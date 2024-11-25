#import "assets/title_page.typ": title_page_me

#import "@preview/codelst:2.0.2": sourcecode

#set text(font: "New Computer Modern", size: 14pt)
#set page(margin: 2cm)
#set heading(numbering: "1.1.1.")

#show heading: it => align(center, it)

#title_page_me(
  7.1,
  [Балансировка дерева поиска]
)

#outline(
  title: [Оглавление]
)

#set page(numbering: "1")
#set par(
  justify: true
)

#pagebreak()

*Цель работы:* изучить абстрактную структуру данных АВЛ-дерево

= Выполнение работы

== Формулировка задачи

Выполнить построение АВЛ-дерева. Реализовать алгоритм вставки узла с балансировкой, симметричный вывод значений элементов, а так же подсчет суммы и среднего арифметического значений элементов АВЛ-дерева.

== Математическая модель

АВЛ-дерево — это сбалансированное двоичное дерево поиска, в котором разница высот поддеревьев любого узла не превышает 1. АВЛ-дерево поддерживает балансировку за счёт операций поворотов (малых и больших) при добавлении или удалении узлов, чтобы поддерживать условие сбалансированности. Это позволяет сохранить временную сложность операций поиска, вставки и удаления на уровне $O(log n)$.

1. Симметричный обход АВЛ-дерева
Симметричный обход АВЛ-дерева означает посещение всех узлов дерева в порядке возрастания их значений. Этот обход начинается с самого левого узла дерева и завершается правым. Для этого:

- Рекурсивно посещаем все узлы в левом поддереве текущего узла;
- Посещаем сам текущий узел и выводим его на экран;
- Рекурсивно посещаем все узлы в правом поддереве текущего узла.

2. Алгоритм нахождения суммы элементов АВЛ-дерева

Чтобы найти сумму всех элементов АВЛ-дерева, выполняем модифицированный симметричный обход, в котором к общей сумме добавляется значение каждого посещенного узла. Процесс можно описать так:

Начинаем с корневого узла и идем в самое левое поддерево.
Для каждого узла рекурсивно суммируем его значение и значения всех узлов его поддеревьев.
Повторяем эти действия для каждого узла дерева, пока не посетим все элементы.
После обхода всех узлов получаем итоговую сумму.

3. Алгоритм нахождения среднего арифметического значений элементов дерева

Чтобы вычислить среднее арифметическое значений узлов, нужны две вещи: общая сумма всех элементов и общее количество узлов дерева. Это можно описать следующим образом:

Во время симметричного обхода находим сумму значений узлов (как в предыдущем алгоритме).
Параллельно или отдельным обходом подсчитываем количество узлов дерева.
В конце делим общую сумму на количество узлов, получая среднее арифметическое.

== Код программы

АВЛ-дерево и вышеописанные алгоритмы были реализованы на языке программирования Go (см. ниже)

#let source = raw(read("work_7-1/avl/avl.go"), lang: "go")

#sourcecode(
  frame: none,
  source
)

#pagebreak()

== Тестирование

Произведем тестирование на 10 элементах

#set figure(supplement: [Рисунок])
#set figure.caption(separator: [ -- ])

#figure(
  caption: [Создание АВЛ-дерева из 10 элементов], 
  image(
    "img/7-1/start.png",
    width: 75%
  )
)

#figure(
  caption: [Симметричный обход АВЛ-дерева], 
  image(
    "img/7-1/inorder.png",
    width: 75%
  )
)

#figure(
  caption: [Вставка элемента и симметричный обход АВЛ-дерева], 
  image(
    "img/7-1/insert_inorder.png",
    width: 75%
  )
)

#figure(
  caption: [Сумма значений элементов АВЛ-дерева], 
  image(
    "img/7-1/sum.png",
    width: 75%
  )
)

#figure(
  caption: [Среднее арифметическое значений элементов АВЛ-дерева], 
  image(
    "img/7-1/inorder.png",
    width: 75%
  )
)

#pagebreak()

= Вывод

В ходе работы было изучено устройство AVL-дерева, его особенности и принципы сбалансированности, которые позволяют эффективно выполнять операции над элементами. Был рассмотрен алгоритм симметричного обхода дерева, позволяющий обрабатывать его узлы в порядке возрастания значений. 

Также были реализованы алгоритмы для нахождения суммы и среднего арифметического значений всех элементов дерева, что позволяет проводить базовый анализ данных в дереве.