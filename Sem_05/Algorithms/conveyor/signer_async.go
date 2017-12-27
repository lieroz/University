package main

import (
	"fmt"
	"sort"
	"strconv"
	"strings"
	"sync"
)

const (
	Th       = 6
	Base     = 10
	sliceLen = 10
)

func ExecutePipeline(jobs ...job) {
	channels := make([]chan interface{}, 0)
	for i := 0; i < len(jobs)+1; i++ {
		channels = append(channels, make(chan interface{}, MaxInputDataLen))
	}
	for i, j := range jobs {
		go func(jb job, in, out chan interface{}) {
			jb(in, out)
			close(out)
		}(j, channels[i], channels[i+1])
	}
	fmt.Println(<-channels[len(jobs)])
}

var m sync.Mutex

func singleHash(out chan interface{}, data string) {
	ch := make(chan string)
	go func(ch chan string) {
		ch <- DataSignerCrc32(<-ch)
	}(ch)
	ch <- data
	m.Lock()
	md5 := DataSignerMd5(data)
	m.Unlock()
	crc32md5 := DataSignerCrc32(md5)
	crc32 := <-ch
	out <- crc32 + "~" + crc32md5
}

func SingleHash(in, out chan interface{}) {
	var wg sync.WaitGroup
	for val := range in {
		data := strconv.FormatInt(int64(val.(int)), Base)
		wg.Add(1)
		go func() {
			defer wg.Done()
			singleHash(out, data)
		}()
	}
	wg.Wait()
}

func multiHash(out chan interface{}, data string) {
	var chs [Th]chan string
	var resultHash string
	for i := 0; i < Th; i++ {
		chs[i] = make(chan string)
		go func(ch chan string, i int) {
			ch <- DataSignerCrc32(strconv.FormatInt(int64(i), Base) + data)
		}(chs[i], i)
	}
	for i := 0; i < Th; i++ {
		resultHash += <-chs[i]
	}
	out <- resultHash
}

func MultiHash(in, out chan interface{}) {
	var wg sync.WaitGroup
	for i := range in {
		data := i.(string)
		wg.Add(1)
		go func() {
			defer wg.Done()
			multiHash(out, data)
		}()
	}
	wg.Wait()
}

func CombineResults(in, out chan interface{}) {
	result := make([]string, 0)
	for val := range in {
		result = append(result, val.(string))
	}
	sort.Strings(result)
	out <- strings.Join(result[:], "_")
}

func fib() func() int {
	a, b := 0, 1
	var tmp int
	return func() int {
		tmp, a, b = a, b, a+b
		return tmp
	}
}

func fill(in, out chan interface{}) {
	f := fib()
	for i := 0; i < sliceLen; i++ {
		out <- f()
	}
}
