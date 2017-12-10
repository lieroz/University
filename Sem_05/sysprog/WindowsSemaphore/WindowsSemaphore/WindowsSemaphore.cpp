// WindowsSemaphore.cpp : Defines the entry point for the console application.
// Реализация монитора Хоара под windows.

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>

const DWORD sleep_time = 50;

const int readers_count = 5;
const int writers_count = 3;
const int iterations = 5;

HANDLE mutex;
HANDLE can_read;
HANDLE can_write;

HANDLE writers[writers_count];
HANDLE readers[readers_count];

volatile LONG active_readers = 0;
bool writing = false;

int value = 0;

void start_read()
{
	if (writing || WaitForSingleObject(can_write, 0) == WAIT_OBJECT_0) {
		WaitForSingleObject(can_read, INFINITE);
	}

	WaitForSingleObject(mutex, INFINITE);
	InterlockedIncrement(&active_readers);
	SetEvent(can_read);
}

void stop_read()
{
	InterlockedDecrement(&active_readers);

	if (active_readers == 0) {
		SetEvent(can_write);
	}

	ReleaseMutex(mutex);
}

void start_write()
{
	if (writing || active_readers > 0) {
		WaitForSingleObject(can_write, INFINITE);
	}

	WaitForSingleObject(mutex, INFINITE);
	writing = true;
}

void stop_write()
{
	writing = false;

	if (WaitForSingleObject(can_read, 0) == WAIT_OBJECT_0) {
		SetEvent(can_read);
	} else {
		SetEvent(can_write);
	}

	ReleaseMutex(mutex);
}

DWORD WINAPI reader(LPVOID)
{
	while (value < writers_count * iterations) {
		start_read();
		Sleep(sleep_time);
		printf("\tReader #%ld read value: %d\n", GetCurrentThreadId(), value);
		stop_read();
		Sleep(sleep_time);
	}

	return 0;
}

DWORD WINAPI writer(LPVOID)
{
	for (int i = 0; i < iterations; i++) {
		start_write();
		Sleep(sleep_time);
		printf("Writer #%ld wrote value: %ld\n", GetCurrentThreadId(), ++value);
		stop_write();
		Sleep(sleep_time);
	}

	return 0;
}

int init_handles()
{
	mutex = CreateMutex(NULL, FALSE, NULL);
	if (mutex == NULL) {
		perror("mutex");
		return EXIT_FAILURE;
	}

	can_read = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (can_read == NULL) {
		printf("can read");
		return EXIT_FAILURE;
	}

	can_write = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (can_write == NULL) {
		printf("can write");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int create_threads()
{
	for (int i = 0; i < writers_count; i++) {
		writers[i] = CreateThread(NULL, 0, writer, NULL, 0, NULL);
		if (writers[i] == NULL) {
			perror("create writer");
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < readers_count; i++) {
		readers[i] = CreateThread(NULL, 0, reader, NULL, 0, NULL);
		if (readers[i] == NULL) {
			perror("create reader");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int main()
{
	int code = EXIT_SUCCESS;

	if ((code = init_handles()) != EXIT_SUCCESS) {
		return code;
	}

	if ((code = create_threads()) != EXIT_SUCCESS) {
		return code;
	}

	WaitForMultipleObjects(writers_count, writers, TRUE, INFINITE);
	WaitForMultipleObjects(readers_count, readers, TRUE, INFINITE);

	CloseHandle(mutex);
	CloseHandle(can_read);
	CloseHandle(can_write);

	system("pause");

	return code;
}
