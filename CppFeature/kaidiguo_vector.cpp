

namespace kaidiguo {

template <typename T> class vector {
private:
  T *data;
  size_t size;
  size_t capacity;

public:
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using iterator = T *;
  using const_iterator = const T *;

  vector() : data(nullptr), size(0), capacity(0) {}

  explicit vector(size_t count)
      : data(new T[count]), size(count), capacity(count) {}

  explicit vector(size_t count, const T &value)
      : data(new T[count]), size(count), capacity(count) {
    for (size_t i = 0; i < count; i++) {
      data[i] = value;
    }
  }

  vector(const vector &other)
      : data(new T[other.size]), size(other.size), capacity(other.capacity) {
    for (size_t i = 0; i < size; i++) {
      data[i] = other.data[i];
    }
  }

  vector(vector &&other) {
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
  }

  vector &operator=(const vector &other) {
    if (this != &other) {
      delete[] data;
      data = new T[other.size];
      size = other.size;
      capacity = other.capacity;
      for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
      }
    }
    return *this;
  }

  vector &operator=(vector &&other) {
    if (this != &other) {
      delete[] data;
      data = other.data;
      size = other.size;
      capacity = other.capacity;
      other.data = nullptr;
      other.size = 0;
      other.capacity = 0;
    }
    return *this;
  }
};

} // namespace kaidiguo