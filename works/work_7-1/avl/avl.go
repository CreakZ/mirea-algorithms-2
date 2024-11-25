package avl

import "fmt"

type avlTree struct {
	value       float64
	left, right *avlTree
	height      int
}

func NewFromSlice(src []float64) *avlTree {
	var tree *avlTree
	for _, value := range src {
		tree = Insert(tree, value)
	}
	return tree
}

func (tree *avlTree) PrintInOrder() {
	if tree != nil {
		tree.left.PrintInOrder()
		fmt.Printf("%f ", tree.value)
		tree.right.PrintInOrder()
	}
}

func (tree *avlTree) Sum() float64 {
	if tree == nil {
		return 0.0
	}
	return tree.value + tree.left.Sum() + tree.right.Sum()
}

func (tree *avlTree) ArithmeticMean() float64 {
	if tree == nil {
		return 0.0
	}
	return tree.Sum() / float64(countTreeNodes(tree))
}

func Insert(tree *avlTree, value float64) *avlTree {
	if tree == nil {
		return &avlTree{value: value, height: 1}
	}

	if value < tree.value {
		tree.left = Insert(tree.left, value)
	} else if value > tree.value {
		tree.right = Insert(tree.right, value)
	} else {
		fmt.Printf("Значение %f уже существует в дереве\n", value)
		return tree
	}

	tree.height = max(getHeight(tree.left), getHeight(tree.right)) + 1

	balance := getBalance(tree)

	if balance > 1 && value < tree.left.value {
		return rightRotation(tree)
	}

	if balance < -1 && value > tree.right.value {
		return leftRotation(tree)
	}

	if balance > 1 && value > tree.left.value {
		tree.left = leftRotation(tree.left)
		return rightRotation(tree)
	}

	if balance < -1 && value < tree.right.value {
		tree.right = rightRotation(tree.right)
		return leftRotation(tree)
	}

	return tree
}

func getHeight(tree *avlTree) int {
	if tree == nil {
		return 0
	}
	return tree.height
}

func getBalance(tree *avlTree) int {
	if tree == nil {
		return 0
	}
	return getHeight(tree.left) - getHeight(tree.right)
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func leftRotation(tree *avlTree) *avlTree {
	y := tree.right
	T2 := y.left

	y.left = tree
	tree.right = T2

	tree.height = max(getHeight(tree.left), getHeight(tree.right)) + 1
	y.height = max(getHeight(y.left), getHeight(y.right)) + 1

	return y
}

func rightRotation(tree *avlTree) *avlTree {
	x := tree.left
	T2 := x.right

	x.right = tree
	tree.left = T2

	tree.height = max(getHeight(tree.left), getHeight(tree.right)) + 1
	x.height = max(getHeight(x.left), getHeight(x.right)) + 1

	return x
}

func countTreeNodes(tree *avlTree) int {
	if tree == nil {
		return 0
	}
	return 1 + countTreeNodes(tree.left) + countTreeNodes(tree.right)
}
