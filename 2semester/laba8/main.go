package main

import (
	"fmt"
	"math/rand"
	"sort"
	"sync"
	"time"
)

// Размер массива для сортировки
const arraySize = 100000

// Функция для генерации случайного массива
func generateRandomArray() []int {
	rand.Seed(time.Now().UnixNano())
	arr := make([]int, arraySize)
	for i := 0; i < arraySize; i++ {
		arr[i] = rand.Intn(100)
	}
	return arr
}

func copyArray(arr []int) []int {
	// Создаем новый срез для копии массива
	new_arr := make([]int, len(arr))

	// Копируем элементы из исходного массива в копию
	copy(new_arr, arr)

	return new_arr
}

// Функция для пузырьковой сортировки
func bubbleSort(arr []int) {
	n := len(arr)
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
			}
		}
	}
}

// Функция для быстрой сортировки
func quickSort(arr []int) {
	if len(arr) <= 1 {
		return
	}
	pivot := arr[len(arr)/2]
	left := make([]int, 0, len(arr))
	right := make([]int, 0, len(arr))
	middle := make([]int, 0, len(arr))
	for _, item := range arr {
		if item < pivot {
			left = append(left, item)
		} else if item > pivot {
			right = append(right, item)
		} else {
			middle = append(middle, item)
		}
	}
	quickSort(left)
	quickSort(right)
	copy(arr, append(append(left, middle...), right...))
}

// Функция для сортировки вставками
func insertionSort(arr []int) {
	for i := 1; i < len(arr); i++ {
		key := arr[i]
		j := i - 1
		for j >= 0 && arr[j] > key {
			arr[j+1] = arr[j]
			j--
		}
		arr[j+1] = key
	}
}

func main() {
	// Генерируем случайный массив
	arr := generateRandomArray()

	// Сортируем массив от меньшего к большему
	sortedAsc := make([]int, len(arr))
	copy(sortedAsc, arr)
	sort.Ints(sortedAsc)

	// Сортируем массив от большего к меньшему
	sortedDesc := make([]int, len(arr))
	copy(sortedDesc, arr)
	sort.Sort(sort.Reverse(sort.IntSlice(sortedDesc)))

	// Запускаем сравнение алгоритмов в параллельном режиме
	var wg sync.WaitGroup
	wg.Add(9)

	go func() {
		defer wg.Done()
		Bubble_rand := copyArray(arr)
		start := time.Now()
		// fmt.Println(Bubble_rand)
		bubbleSort(Bubble_rand)
		fmt.Println("Bubble sort (random array) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Bubble_sortedAsc := copyArray(sortedAsc)
		start := time.Now()
		// fmt.Println(Bubble_sortedAsc)
		bubbleSort(Bubble_sortedAsc)
		fmt.Println("Bubble sort (sorted ascending) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Bubble_sortedDesc := copyArray(sortedDesc)
		start := time.Now()
		// fmt.Println(Bubble_sortedDesc)
		bubbleSort(Bubble_sortedDesc)
		fmt.Println("Bubble sort (sorted descending) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Quick_rand := copyArray(arr)
		start := time.Now()
		// fmt.Println(Quick_rand)
		quickSort(Quick_rand)
		fmt.Println("Quick sort (random array) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Quick_sortedAsc := copyArray(sortedAsc)
		start := time.Now()
		// fmt.Println(Quick_sortedAsc)
		quickSort(Quick_sortedAsc)
		fmt.Println("Quick sort (sorted ascending) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Quick_sortedDesc := copyArray(sortedDesc)
		start := time.Now()
		// fmt.Println(Quick_sortedDesc)
		quickSort(Quick_sortedDesc)
		fmt.Println("Quick sort (sorted descending) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Insert_random := copyArray(arr)
		start := time.Now()
		// fmt.Println(Insert_random)
		insertionSort(Insert_random)
		fmt.Println("Insert sort (random array) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Insert_sortedAsc := copyArray(sortedAsc)
		start := time.Now()
		// fmt.Println(Insert_sortedAsc)
		insertionSort(Insert_sortedAsc)
		fmt.Println("Insert sort (sorted ascending) duration:", time.Since(start))
	}()

	go func() {
		defer wg.Done()
		Insert_sortedDesc := copyArray(sortedDesc)
		start := time.Now()
		// fmt.Println(Insert_sortedDesc)
		insertionSort(Insert_sortedDesc)
		fmt.Println("Insert sort (sorted descending) duration:", time.Since(start))
	}()

	wg.Wait()
}
