#let title_page(
  num,
  subject,
  title,
  professor_name
) = {
  set text(14pt, font: "New Computer Modern")
  set align(center)
  set page(margin: 2cm)

  image("logo.png")

  text(12pt, [МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ \
  ФЕДЕРАЛЬНОЕ ГОСУДАРСТВЕННОЕ БЮДЖЕТНОЕ ОБРАЗОВАТЕЛЬНОЕ УЧРЕЖДЕНИЕ ВЫСШЕГО ОБРАЗОВАНИЯ \
  *«МИРЭА – Российский технологический университет»*])

  linebreak()

  v(0.65em)

  text(16pt, [*РТУ МИРЭА*])

  v(0.65em)

  line(length: 100%, stroke: 1pt)  

  v(1fr)

  text([*ОТЧЕТ ПО ПРАКТИЧЕСКОЙ РАБОТЕ №#num* \ *по дисциплине* 
  \ $quote.l.angle.double$#subject$quote.r.angle.double$ \
  Тема $quote.l.angle.double$#title$quote.r.angle.double$])

  v(1fr)

  stack(
    dir: ttb,
    text([Выполнил студент группы ИКБО-13-23 #h(1fr) Русаков М.Ю.]),

    v(3 * 0.65em),

    text([Принял преподаватель #h(1fr) #professor_name])
  )

  v(1fr)

  let year = datetime.today().year()

  text([Москва #year г.])
}

#let title_page_me(
  num, 
  title
) = {
  title_page(
    num, 
    [Структуры и алгоритмы обработки данных],
    title,
    [Сорокин А.В.]
  )
}
