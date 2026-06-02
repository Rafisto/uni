; binomial

; zerop k === k = 0
; () evaluates to nil/false so must wrap with t()
(defun binomial (n k)
  (cond ((zerop k) 1)
        ((> k n) 0)
        ((= k n) 1)
        (t (+ (binomial (1- n) k)
              (binomial (1- n) (1- k))))))

; binomial2

; zip with + + mapcar #'+ 
(defun ptr (x)
  (cond ((zerop x) '(1))
        ((= x 1) '(1 1))
        (t (let ((prev (ptr (1- x))))
             (mapcar #'+ 
                     (append prev '(0)) 
                     (append '(0) prev))))))

(defun binomial2 (n k)
  (cond ((zerop k) 1)
        ((> k n) 0)
        ((= k n) 1)
        (t (nth k (ptr n)))))

; mergesort

; x:xs === car:cdr
; predicate = order
(defun merge_lists (predicate a b)
  (cond ((null a) b)
        ((null b) a)
        ((funcall predicate (car a) (car b))
         (cons (car a) (merge_lists predicate (cdr a) b)))
        (t (cons (car b) (merge_lists predicate a (cdr b))))))

(defun mergesort (xs)
  (let ((len (length xs)))
    (if (< len 2)
        xs
        (let* ((mid (floor len 2))
               (left (subseq xs 0 mid))
               (right (subseq xs mid)))
          ; pass order <=  
          (merge_lists #'<= (mergesort left) (mergesort right))))))

; de

(defun mgcd (x y)
  (cond ((zerop x) y)
        ((zerop y) x)
        ((> x y) (mgcd y (mod x y)))
        ((< x y) (mgcd x (mod y x)))
        (t x)))

(defun de (a b)
  (if (zerop b)
      (values 1 0 a)
      ; tuple destructuring
      (multiple-value-bind (x1 y1 g) (de b (mod a b))
        (values y1
                (- x1 (* (floor a b) y1)) 
                g))))

; prime_factors

(defun prime_factors (n)
  (labels ((dv (acc c n)
             (cond ((= n 1) (reverse acc))
                   ((zerop (mod n c)) (dv (cons c acc) 2 (/ n c)))
                   (t (dv acc (1+ c) n)))))
    (if (<= n 1) nil (dv nil 2 n))))

; totient

(defun totient (n)
  (labels ((count_relative_primes (k acc)
             (cond ((zerop k) acc)
                   ((= 1 (gcd k n)) 
                    (count_relative_primes (1- k) (1+ acc)))
                   (t (count_relative_primes (1- k) acc)))))
    (if (<= n 0)
        0
        (count_relative_primes n 0))))

; totient 2

(defun range (a b)
  (if (> a b)
      nil
      (cons a (range (1+ a) b))))

(defun primes (n)
  (labels ((eval_sieve (lst)
             (if (null lst)
                 nil
                 (let ((x (car lst)))
                   ; cons 1 '(2 3 4) = (1 2 3 4)
                   (cons x (eval_sieve (remove-if (lambda (i) (zerop (mod i x))) (cdr lst))))))))
    (if (<= n 1) nil (eval_sieve (range 2 n)))))

(defun totient2 (n)
  (if (<= n 1)
      1
      (let* ((pf (prime_factors n))
             (so (remove-duplicates pf))
             (s1 (mapcar #'1- so))
             (s2 (let ((temp-pf pf))
                   (dolist (x so temp-pf)
                     ; remove single occurrence
                     (setf temp-pf (remove x temp-pf :count 1))))))
        (reduce #'* (append s1 s2)))))

(defun main ()
  (format t "~D~%" (binomial 4 2))
  (format t "~D~%" (binomial2 4 2))
  (format t "~D~%" (mgcd 24 18))
  
  (let ((sorted (mergesort '(0 2 4 6 8 1 3 5 7 9))))
    (format t "~{~D ~}~%" sorted))

  (multiple-value-bind (x y g) (de 7 3)
    (format t "x: ~D y: ~D mod: ~D~%" x y g))

  (format t "~{~D ~}~%" (prime_factors 60))
  (format t "~D~%" (totient 1000))
  (format t "~D~%" (totient2 1000))
  (format t "~{~D ~}~%" (primes 30)))

(main)
