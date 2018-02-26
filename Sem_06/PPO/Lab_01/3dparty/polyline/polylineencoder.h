/*
MIT License

Copyright (c) 2017 Vahan Aghajanyan <vahancho@gmail.com>
Copyright (c) 2018 Andrey Kamakin <a.kamakin@icloud.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef POLYLINEENCODER_H
#define POLYLINEENCODER_H

#include <QPointF>
#include <QVector>
#include <QReadWriteLock>

//! Implements Google's polyline compression algorithm.
/*!
  For more details refer to the algorithm definition at
  https://developers.google.com/maps/documentation/utilities/polylinealgorithm
*/
class PolylineEncoder
{
public:
    PolylineEncoder();
    PolylineEncoder(const PolylineEncoder &encoder);
    ~PolylineEncoder();

    PolylineEncoder &operator=(const PolylineEncoder &encoder);

    //! Adds new point with the given \p point for encoding.
    void addPoint(const QPointF &point);

    //! Adds new points with the given \p points for encoding.
    void addPoints(const QVector<QPointF> &points);

    //! Adds new point with the given \p point for encoding.
    void insertPoint(qint32 index, const QPointF &point);

    //! Adds new points with the given \p points for encoding.
    void insertPoints(qint32 index, const QVector<QPointF> &points);

    //! Removes point at the given \p position index.
    void removePoint(qint32 index);

    //! Removes points starting from the given \p position index.
    void removePoints(qint32 index, qint32 n);

    //! Relpaces point at the given \p position index.
    void replacePoint(qint32 index, const QPointF &point);

    //! Replaces points starting from the given \p position index.
    void replacePoints(qint32 index, const QVector<QPointF> &points);

    //! Encode the polyline according to the defined compression algorithm.
    /*!
    \return The encoded polyline as string.
    */
    QString encode();

    //! Returns the existing polyline.
    const QVector<QPointF> &polyline();

    //! Clears the list of polyline.
    void clear();

    //! Returns the result of encoding of the given polyline.
    static QString encode(const QVector<QPointF> &polyline);

    //! Returns polyline decoded from the given \p coordinates string.
    static QVector<QPointF> decode(const QString &coordinates);

private:
    //! Encodes a single value according to the compression algorithm.
    static QString encode(qreal value);

    //! Decodes the current decimal value out of string.
    static qreal decode(const QString &coords, size_t &i);

    //! Store the polyline - the list of points.
    QVector<QPointF> m_polyline;
    QReadWriteLock m_rwlock;
};

#endif // POLYLINEENCODER_H
