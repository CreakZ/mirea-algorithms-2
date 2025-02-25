use std::{io::{self, Write}, vec};

#[allow(dead_code)]
fn longest_word_with_common_first_last(text: String) -> Option<String> {
    if text.is_empty() {
        return None;
    }

    text.split(' ')
        .map(|word| word.to_string().to_lowercase())
        .filter(|word| {
            word.chars().next().unwrap() == word.chars().last().unwrap()
        })
        .max_by_key(|word| word.len())
}

fn prefix_function(s: String) -> Vec<usize> {
    let mut prefix = vec![0; s.len()];
    let mut j = 0;

    for i in 1..s.len() {
        while j > 0 && s.as_bytes()[i] != s.as_bytes()[j] {
            j = prefix[j - 1];
        }
        if s.as_bytes()[i] == s.as_bytes()[j] {
            j += 1;
        }
        prefix[i] = j;
    }

    prefix
}

fn kmp_search(text: String, pattern: &str) -> Option<usize> {
    let prefix = prefix_function(text.clone());
    let mut last = None;
    let mut j = 0;

    for i in 0..text.len() {
        while j > 0 && text.as_bytes()[i] != pattern.as_bytes()[j] {
            j = prefix[j - 1];
        }
        if text.as_bytes()[i] == pattern.as_bytes()[j] {
            j += 1;
        }
        if j == pattern.len() {
            last = Some(i + 1 - j);
            j = prefix[j - 1];
        }
    }

    last
}

fn main() {
    print!("введите ваш текст: ");
    io::stdout().flush().expect("ошибка закрытия потока ввода");

    let mut text = String::new();
    io::stdin().read_line(&mut text).expect("ошибка ввода текста");

    print!("введите ваш образец: ");
    io::stdout().flush().expect("ошибка закрытия потока ввода");

    let mut pattern = String::new();
    io::stdin().read_line(&mut pattern).expect("ошибка ввода образца");

    match kmp_search(text, pattern.as_str()) {
        Some(size) => println!("последнее вхождение: {size}"),
        None => println!("искомый образец не встречается в введенном тексте")
    }
}
