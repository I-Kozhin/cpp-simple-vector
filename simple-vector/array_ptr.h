#pragma once

#include <cassert>
#include <cstdlib>
#include <algorithm>

template <typename Type>
class ArrayPtr {
public:
	
	ArrayPtr() = default; //ArrayPtr инициализируется нулевым указателем

	// Создаёт в куче массив из size элементов типа Type.
	// Если size == 0, поле raw_ptr_ должно быть равно nullptr
	explicit ArrayPtr(size_t size) {
		if (size == 0) { raw_ptr_ = nullptr; }
		else {
			raw_ptr_ = new Type[size];
		}

	}

	// Конструктор из сырого указателя, хранящего адрес массива в куче либо nullptr
	explicit ArrayPtr(Type* raw_ptr) noexcept {
		raw_ptr_ = raw_ptr;
	}
    
    	// Конструктор из сырого указателя, хранящего адрес массива в куче либо nullptr
        // должен обменивать указатели, устанавливая указатель другого объекта в nullptr
	explicit ArrayPtr(ArrayPtr<Type>&& other) noexcept {
		raw_ptr_.swap(other.raw_ptr_);
        other.raw_ptr_ = nullptr;
	}
    
	ArrayPtr(const ArrayPtr&) = delete; // Копирование запрещено

	~ArrayPtr() {
		delete[] raw_ptr_;
	}

	ArrayPtr& operator=(const ArrayPtr&) = delete;  // Присваивание запрещено
    
    
    //Оператор присваивания для ArrayPtr<Type>&&
    ArrayPtr&& operator=(ArrayPtr&& other ) {
        // если адреса объектов не совпадают, то их указатели обмениваются
        if (raw_ptr_ != other.raw_ptr_) {
        raw_ptr_.swap(other.raw_ptr_);
        }
    };
    

	// Прекращает владением массивом в памяти, возвращает значение адреса массива
	// После вызова метода указатель на массив должен обнулиться
	[[nodiscard]] Type* Release() noexcept {

		Type* p = raw_ptr_;
		raw_ptr_ = nullptr;
		return p;
	}

	// Возвращает ссылку на элемент массива с индексом index
	Type& operator[](size_t index) noexcept {

		return raw_ptr_[index];
	}

	// Возвращает константную ссылку на элемент массива с индексом index
	const Type& operator[](size_t index) const noexcept {


		return  raw_ptr_[index];
	}

	// Возвращает true, если указатель ненулевой, и false в противном случае
	explicit operator bool() const {

		if (raw_ptr_) { return true; }
		else {
			return false;
		}
	}

	// Возвращает значение сырого указателя, хранящего адрес начала массива
	Type* Get() const noexcept {

		return raw_ptr_;
	}

	// Обмен значениями указателя на массив с объектом other
	void swap(ArrayPtr& other) noexcept {
        std::swap(raw_ptr_, other.raw_ptr_);
	}



private:
	Type* raw_ptr_ = nullptr;
};