/**
 * @file mymatrix.h
 * @brief Заголовочный файл, содержащий определение класса MyMatrix для работы с матрицами.
 */


#ifndef MYMATRIX_H
#define MYMATRIX_H



#include <type_traits>
#include <stdexcept>
#include <iostream>


/**
 * @class MatrixIterator
 * @brief Итератор для работы с элементами матрицы, удовлетворяющий требованиям
 *        random access iterator.
 * 
 * @tparam T Тип элементов, на которые указывает итератор.
 * @tparam is_const Указывает, является ли итератор константным.
 *         Если `true`, итератор работает с `const T`, иначе — с `T`.
 */
template<typename T, bool is_const>
class MatrixIterator {
public:

  /*!
   * @brief Тип, обозначающий дистанцию между двумя итераторами,
   *        т.е. результат std::distance(it1, it2)
   */
    using difference_type = ptrdiff_t;

  /*!
   * @brief Адресуемый итератором тип
   */
    using value_type = T;

  /*!
   * @brief Тип указателя на хранимое значение,
   *        для const_iterator - const T*, для обычного - T*
   */
    using pointer = std::conditional_t<is_const, const T, T>*;

  /*!
   * @brief Тип ссылки на хранимое значение,
   *        для const_iterator - const T&, для обычного - T&
   */
    using reference = std::conditional_t<is_const, const T, T>&;

  /*!
   * @brief Категория итератора
   */
    using iterator_category = std::random_access_iterator_tag;

  /*!
   * @brief Пустой конструктор, разименование созданного итератора приведёт к UB
   * @note Реализует default_initializable из regular
   */
    MatrixIterator() noexcept = default;

  /*!
   * @brief Копирующий крнструктор
   * @tparam other_const Константность копируемого иетратора
   * @note Допускает копирование итератора иной константности
   * @note Реализует std::move_constructible и std::copy_constructible
   */
    template<bool other_const>
    MatrixIterator(const MatrixIterator<T, other_const>& other) noexcept
        // нельзя из неконстантного в константный
        requires (is_const >= other_const)
        : data_(other.data_) {}

    MatrixIterator(pointer ptr) noexcept : data_(ptr) {}

  /*!
   * @brief Разыменование
   * @returns Ссылка на адресуемый элемент списка
   * @note Реализует `{ *i } -> / *can-reference* /` из input_or_output_iterator и indirectly_readable
   */
    reference operator*() const noexcept { return *data_; }

  /*!
   * @brief Обрщение к полям элемента
   * @returns Указатель на адресуемый элемент списка
   */
    pointer operator->() const noexcept { return data_; }

  /*!
   * @brief Сравнение итераторов
   * @tparam other_const Константность копируемого иетратора
   * @returns true если итераторы ссылаются на один и тот же элемент,
   *          иначе false
   * @note Реализует equality_comparable из regular
   * @note Опрератор != получаем автоматически
   */
    template<bool other_const>
    bool operator==(const MatrixIterator<T, other_const>& other) const noexcept { return data_ == other.data_; }

  /*!
   * @brief Передвигает итератор на следующий элемент списка
   * @returns Ссылка на переданный итератор
   * @note Реализует `{ ++i } -> std::same_as<I&>` из weakly_incrementable
   */
    MatrixIterator& operator++() noexcept {
        data_++;
        return *this;
    }

  /*!
   * @brief Передвигает итератор на следующий элемент списка
   * @returns Состояние итератора до модификации
   * @note Реализует `{ i++ } -> std::same_as<I>` из incrementable
   */
    MatrixIterator operator++(int) noexcept {
        MatrixIterator temp = *this;
        ++(*this);
        return temp;
    }

  /*!
   * @brief Передвигает итератор на предыдущий элемент списка
   * @returns Ссылка на переданный итератор
   * @note Реализует `{ --i } -> std::same_as<I&>` из bidirectional_iterator
   */
    MatrixIterator& operator--() noexcept {
        --data_;
        return *this;
    }

  /*!
   * @brief Передвигает итератор на предыдущий элемент списка
   * @returns Состояние итератора до модификации
   * @note Реализует `{ i-- } -> std::same_as<I>` из bidirectional_iterator
   */
    MatrixIterator operator--(int) noexcept {
        MatrixIterator temp = *this;
        --(*this);
        return temp;
    }

  /*!
   * @brief Сложение итератора с числом.
   * @param value Смещение в элементах, на которое нужно передвинуть итератор вперёд.
   * @returns Новый итератор, смещённый на `value` элементов.
   * @note Реализует `{ i + n } -> std::same_as<I>` из random_access_iterator.
   */
    MatrixIterator operator+(difference_type value) const noexcept { return MatrixIterator(data_ + value); }

  /*!
   * @brief Сложение числа с итератором.
   * @param value Смещение в элементах, на которое нужно передвинуть итератор вперёд.
   * @param other Итератор, который нужно сместить.
   * @returns Новый итератор, смещённый на `value` элементов.
   * @note Реализует  `{ n +  j } -> std::same_as<I>` из random_access_iterator.
   */
    friend MatrixIterator operator+(difference_type value, const MatrixIterator& other){
        return MatrixIterator(other + value);
    }

  /*!
   * @brief Сложение с числом.
   * @param value Смещение в элементах, на которое нужно передвинуть итератор вперёд.
   * @returns Ссылка на текущий итератор после изменения.
   * @note Реализует `{ i += n } -> std::same_as<I&>` из random_access_iterator.
   */
    MatrixIterator& operator+=(difference_type value) noexcept {
        data_ += value;
        return *this;
    }

  /*!
   * @brief Вычитание числа из итератора.
   * @param value Смещение в элементах, на которое нужно передвинуть итератор назад.
   * @returns Новый итератор, смещённый на `value` элементов назад.
   * @note Реализует `{ i - n } -> std::same_as<I>` из random_access_iterator.
   */
    MatrixIterator operator-(difference_type value) const noexcept { return MatrixIterator(data_ - value); }

  /*!
   * @brief Вычитание числа из итератора.
   * @param value Смещение в элементах, на которое нужно передвинуть итератор назад.
   * @returns Ссылка на текущий итератор после изменения.
   * @note Реализует `{ i -= n } -> std::same_as<I&>` из random_access_iterator.
   */
    MatrixIterator& operator-=(difference_type value) noexcept {
        data_ -= value;
        return *this;
    }

  /*!
   * @brief Вычисление разницы между двумя итераторами.
   * @param other Другой итератор.
   * @returns Количество элементов между текущим и переданным итератором.
   * @note Реализует `{ i - j } -> std::same_as<difference_type>` из random_access_iterator.
   */
    difference_type operator-(const MatrixIterator& other) const noexcept { return data_ - other.data_; }

  /*!
   * @brief Индексация относительно итератора.
   * @param value Смещение в элементах от текущей позиции итератора.
   * @returns Ссылка на элемент, расположенный на `value` элементов от текущей позиции.
   * @note Реализует `{ i[n] } -> std::same_as<reference>` из random_access_iterator.
   */
    reference operator[](difference_type value) const noexcept { return *(data_ + value); }

  /*!
   * @brief Сравнение двух итераторов (трёхсторонний оператор spaceship).
   * @returns Результат сравнения текущего итератора с другим.
   * @note Реализует `<=>` (std::totally_ordered<I>) для сравнения итераторов по их позициям.
   */
    auto operator<=>(const MatrixIterator& other) const = default;

private:
    pointer data_ = nullptr; ///< Указатель на текущий элемент.
};

static_assert(std::random_access_iterator<MatrixIterator<int, true>>);
static_assert(std::random_access_iterator<MatrixIterator<int, false>>);


/**
 * @brief Класс для работы с матрицами.
 * 
 * Шаблонный класс для хранения и работы с двумерными массивами.
 * Поддерживает доступ через операторы `[]`, итераторы и изменение размеров.
 * 
 * @tparam T Тип элементов матрицы.
 */
template <std::default_initializable T>
class MyMatrix {
private:
    std::size_t rows_;      ///< Количество строк в матрице.
    std::size_t columns_;   ///< Количество столбцов в матрице.
    T* data_;               ///< Указатель на данные матрицы.

    // Внутренний класс для работы с отдельными строками
    class RowsClass {
    private:
        std::size_t columns_; ///< Количество столбцов в строке.
        T* row_data_;         ///< Указатель на данные строки.

    public:

        /**
         * @brief Конструктор строки.
         * @param columns Количество столбцов.
         * @param row_data Указатель на данные строки.
         */
        RowsClass(std::size_t columns, T* row_data) : columns_(columns), row_data_(row_data) {}

        /**
         * @brief Доступ к элементу строки по индексу.
         * @param col Индекс столбца.
         * @return Ссылка на элемент строки.
         * @throws std::out_of_range Если индекс выходит за пределы столбцов.
         */
        T& operator[](std::size_t col) {
            if (col >= columns_){
                throw std::out_of_range("Column index out of range");
            }
            return row_data_[col];
        }

        /**
         * @brief Доступ к элементу строки по индексу (константный).
         * @param col Индекс столбца.
         * @return Константная ссылка на элемент строки.
         * @throws std::out_of_range Если индекс выходит за пределы столбцов.
         */
        const T& operator[](std::size_t col) const {
            if (col >= columns_){
                throw std::out_of_range("Column index out of range");
            }
            return row_data_[col];
        }
    };

public:
    using iterator = MatrixIterator<T, false>;      ///< Итератор для доступа к элементам матрицы.
    using const_iterator = MatrixIterator<T, true>; ///< Константный итератор для доступа к элементам матрицы.

    /**
     * @brief Конструктор по умолчанию.
     * 
     * Создает пустую матрицу с нулевыми размерами.
     */
    MyMatrix() : rows_(0), columns_(0), data_(nullptr) {}

    /**
     * @brief Конструктор с заданными размерами.
     * @param rows Количество строк.
     * @param columns Количество столбцов.
     * @param default_value Значение для инициализации элементов матрицы (по умолчанию T()).
     */
    MyMatrix(std::size_t rows, std::size_t columns, const T& default_value = T())
        : rows_(rows), columns_(columns), data_(new T[rows * columns]) {
        std::fill(data_, data_ + rows_ * columns_, default_value);
    }

    /**
     * @brief Копирующий конструктор.
     * @param other Матрица для копирования.
     */
    MyMatrix(const MyMatrix& other)
        : rows_(other.rows_), columns_(other.columns_), data_(new T[other.rows_ * other.columns_]) {
        std::copy(other.data_, other.data_ + rows_ * columns_, data_);
    }

    /**
     * @brief Копирующий оператор присваивания.
     * @param other Матрица для копирования.
     * @return Ссылка на текущую матрицу.
     */
    MyMatrix& operator=(const MyMatrix& other) {
        if (this != &other) {
            delete[] data_;
            rows_ = other.rows_;
            columns_ = other.columns_;
            data_ = new T[rows_ * columns_];
            std::copy(other.data_, other.data_ + rows_ * columns_, data_);
        }
        return *this;
    }

    /**
     * @brief Перемещающий конструктор.
     * @param other Матрица, из которой перенимаются данные.
     */
    MyMatrix(MyMatrix&& other) noexcept
        : rows_(other.rows_), columns_(other.columns_), data_(other.data_) {
        other.data_ = nullptr;
        other.rows_ = 0;
        other.columns_ = 0;
    }

    /**
     * @brief Перемещающий оператор присваивания.
     * @param other Матрица, из которой перенимаются данные.
     * @return Ссылка на текущую матрицу.
     */
    MyMatrix& operator=(MyMatrix&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            rows_ = other.rows_;
            columns_ = other.columns_;
            other.data_ = nullptr;
            other.rows_ = 0;
            other.columns_ = 0;
        }
        return *this;
    }

    /**
     * @brief Деструктор.
     * 
     * Освобождает память, занятую матрицей.
     */
    ~MyMatrix() {
        delete[] data_;
    }

    /**
     * @brief Доступ к строке матрицы по индексу.
     * @param row Индекс строки.
     * @return Объект строки, предоставляющий доступ к элементам.
     * @throws std::out_of_range Если индекс строки выходит за пределы.
     */
    RowsClass operator[](std::size_t row) {
        if (row >= rows_){
            throw std::out_of_range("Row index out of range");
        }
        return RowsClass(columns_, data_ + row * columns_);
    }

    /**
     * @brief Доступ к строке матрицы по индексу (константный).
     * @param row Индекс строки.
     * @return Объект строки, предоставляющий доступ к элементам (константный).
     * @throws std::out_of_range Если индекс строки выходит за пределы.
     */
    const RowsClass operator[](std::size_t row) const {
        if (row >= rows_){
            throw std::out_of_range("Row index out of range");
        }
        return RowsClass(columns_, data_ + row * columns_);
    }

    /**
     * @brief Получение количества строк матрицы.
     * @return Количество строк.
     */
    std::size_t rows() const noexcept { return rows_; }

    /**
     * @brief Получение количества столбцов матрицы.
     * @return Количество столбцов.
     */
    std::size_t columns() const noexcept { return columns_; }

    /**
     * @brief Итератор на начало матрицы.
     * @return Итератор на первый элемент.
     */
    iterator begin() noexcept { return iterator(data_); }

    /**
     * @brief Итератор на конец матрицы.
     * @return Итератор на элемент, следующий за последним.
     */
    iterator end() noexcept { return iterator(data_ + rows_ * columns_); }


    /**
     * @brief Константный итератор на начало матрицы.
     * @return Константный итератор на первый элемент (аналог begin()).
     */
    const_iterator cbegin() const noexcept { return const_iterator(data_); }

    /**
     * @brief Константный итератор на конец матрицы.
     * @return Константный итератор на элемент, следующий за последним (аналог end()).
     */
    const_iterator cend() const noexcept { return const_iterator(data_ + rows_ * columns_); }

   /**
     * @brief Изменение размеров матрицы.
     * @param new_rows Новое количество строк.
     * @param new_columns Новое количество столбцов.
     * @param default_value Значение для заполнения новых элементов (по умолчанию T()).
     */
    void resize(std::size_t new_rows, std::size_t new_columns, const T& default_value = T()) {
        T* new_data = new T[new_rows * new_columns];
        std::fill(new_data, new_data + new_rows * new_columns, default_value);

        std::size_t min_rows = std::min(rows_, new_rows);
        std::size_t min_columns = std::min(columns_, new_columns);

        for (std::size_t i = 0; i < min_rows; i++){
            for (std::size_t j = 0; j < min_columns; j++){
                new_data[i * new_columns + j] = (*this)[i][j];
            }
        }

        delete[] data_;
        data_ = new_data;
        rows_ = new_rows;
        columns_ = new_columns;
    }

    /**
     * @brief Очистка матрицы.
     * 
     * Удаляет все элементы и устанавливает размеры в ноль.
     */
    void clear() {
        delete[] data_;
        data_ = nullptr;
        rows_ = 0;
        columns_ = 0;
    }
};

#endif // MYMATRIX_H