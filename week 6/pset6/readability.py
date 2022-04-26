from cs50 import get_string


def main():
    s = get_string("Text: ")
    letters = count_letters(s)
    words = count_words(s)
    sent = count_sent(s)

    L = letters * 100 / words
    S = sent * 100 / words
    index = 0.0588 * L - 0.296 * S - 15.8

    ans = round(index)
    if ans < 1:
        print("Before Grade 1")
    elif ans > 16:
        print("Grade 16+")
    else:
        print(f"Grade {ans}")
        

def count_letters(s):
    ans = 0
    for c in s:
        if c.isalpha():
            ans += 1
    return ans
    

def count_words(s):
    ans = 1
    for c in s:
        if c == " ":
            ans += 1
    return ans
    

def count_sent(s):
    ans = 0
    for c in s:
        if c == "." or c == "!" or c == "?":
            ans += 1
    return ans
    

main()