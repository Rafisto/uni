-- Zadanie 30 — Funkcja filter może myć zdefiniowana za pomocą funkcji map i concat:
-- filter p = concat . map box
-- where box x =
-- Podaj definicję tej funkcji box.

filter' :: (a -> Bool) -> [a] -> [a]
filter' p = concat . map box
    where box x = if p x then [x] else []
