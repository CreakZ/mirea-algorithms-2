package main

import (
	"avltree/avl"
	"fmt"
	"os"
)

const menuText = `
Введите желаемое действие с АВЛ-деревом:
	1. Вставка элемента
	2. Симметричный обход дерева
	3. Вывод суммы значений дерева
	4. Вывод среднего арифметического значений дерева
	5. Выход`

func main() {
	var amount int
	fmt.Printf("Введите количество элементов дерева: ")
	if _, err := fmt.Scan(&amount); err != nil {
		fmt.Printf("ошибка чтения ввода: %s\n", err.Error())
		return
	}

	values := make([]float64, amount)

	var value float64
	for i := range amount {
		for {
			fmt.Printf("Введите значение %d-й переменной: ", i+1)
			if _, err := fmt.Scan(&value); err != nil {
				fmt.Printf("%d: %s\n", i, err.Error())
			} else {
				break
			}
		}
		values[i] = value
	}

	tree := avl.NewFromSlice(values)

	var option uint8
	for {
		fmt.Printf("%s\nВыбор: ", menuText)
		if _, err := fmt.Scan(&option); err != nil {
			fmt.Printf("ошибка чтения ввода: %s\n", err.Error())
			break
		}
		fmt.Printf("\n")

		switch option {
		case 1:
			var toInsert float64
			fmt.Printf("Введите значение: ")
			if _, err := fmt.Scan(&toInsert); err != nil {
				fmt.Printf("ошибка чтения ввода: %s\n", err.Error())
				continue
			}
			tree = avl.Insert(tree, toInsert)
			fmt.Printf("Значение %f вставлено успешно.\n", toInsert)
		case 2:
			tree.PrintInOrder()
			fmt.Printf("\n")
		case 3:
			fmt.Printf("Сумма значений элементов дерева = %f\n", tree.Sum())
		case 4:
			fmt.Printf("Среднее арифметическое значений элементов дерева = %f\n", tree.ArithmeticMean())
		case 5:
			os.Exit(0)
		}
	}
}
