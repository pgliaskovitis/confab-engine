#ifndef DOKEXCITATIONVECTOR_H
#define DOKEXCITATIONVECTOR_H

#include <unordered_map>

#include "Utils.h"
#include "IExcitationVector.hpp"

template <typename T>
class DOKExcitationVector : public IExcitationVector<T>
{
public:
    DOKExcitationVector(const size_t num_rows);
    DOKExcitationVector(const IExcitationVector<T>& base);

    DOKExcitationVector(const DOKExcitationVector& rhs) = delete;
    DOKExcitationVector& operator=(const DOKExcitationVector& rhs) = delete;
    DOKExcitationVector(DOKExcitationVector&& rhs) = delete;
    DOKExcitationVector&& operator=(DOKExcitationVector&& rhs) = delete;

    virtual void SetElement(const size_t r, const T& value);
    virtual void SetElementQuick(const size_t r, const T& value);

    virtual const T& GetElement(const size_t r) const;
    virtual const T& GetElementQuick(const size_t r) const;

    virtual size_t get_num_rows() const { return num_rows_; }

    virtual size_t GetNnz() const { return map_.size(); }

    virtual void Add(const IExcitationVector<T>& other);
    virtual std::set<std::pair<size_t, T>> GetNzElements() const;

private:
    const size_t num_rows_;

    std::unordered_map<size_t, T> map_;
};

template <typename T>
DOKExcitationVector<T>::DOKExcitationVector(const size_t num_rows) : num_rows_(num_rows)
{}

template <typename T>
DOKExcitationVector<T>::DOKExcitationVector(const IExcitationVector<T> &base) : num_rows_(base.get_num_rows())
{
    for (const std::pair<size_t, T>& element : base.GetNzElements())
        map_[element.first] = element.second;
}

template <typename T>
void DOKExcitationVector<T>::SetElement(const size_t r, const T& value)
{
    IExcitationVector<T>::CheckBounds(r);
    if (IsNearlyEqual(value, 0)) {
        typename std::unordered_map<size_t, T>::iterator it = map_.find(r);
        if (it != map_.end())
            map_.erase(it);
    } else
        SetElementQuick(r, value);
}

template <typename T>
void DOKExcitationVector<T>::SetElementQuick(const size_t r, const T &value)
{
    map_[r] = value;
}

template <typename T>
const T& DOKExcitationVector<T>::GetElement(const size_t r) const
{
    IExcitationVector<T>::CheckBounds(r);
    return GetElementQuick(r);
}

template <typename T>
const T& DOKExcitationVector<T>::GetElementQuick(const size_t r) const
{
    T result;

    try {
        result = map_.at(r);
    } catch (const std::out_of_range& oor) {
        result = 0;
    }

    return result;
}

template <typename T>
void DOKExcitationVector<T>::Add(const IExcitationVector<T>& other) {
    for (const std::pair<size_t, T>& element : other.GetNzElements()) {
        SetElement(element.first, PositiveClip(element.second + GetElement(element.first)));
    }
}

template <typename T>
std::set<std::pair<size_t, T>> DOKExcitationVector<T>::GetNzElements() const
{
    typename std::set<std::pair<size_t, T>> result;
    for (typename std::unordered_map<size_t, T>::const_iterator it = map_.begin(); it != map_.end(); ++it)
        result.insert(*it);

    return result;
}

#endif // DOKEXCITATIONVECTOR_H
