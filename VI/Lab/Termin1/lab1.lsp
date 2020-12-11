(defun umetnil (el n ind lista rezultat)
  (cond (equal n ind) (
                       (append rezultat n)
                       (append rezultat lista)
                       )
        (t (
            (umetnil el n (+ ind 1) (cdr lista) (append rezultat (car lista)))
           ))
  )
)

(defun umetni (el n lista)
  (umetnil el n 0 lista '())
  )

(umetni ’d ’3 ’(a b c e f))

;gnu clisp  2.49.60


(defun promeni (n lista)
    (
     cond ((null lista) '())
         ((> n 0) (append (list (+ (car lista) 1)) (promeni (- n 1) (cdr lista))))
         (t (append (list (- (car lista) 1)) (promeni n (cdr lista))))
     )
)

(print (promeni 1 '(2 3 4 5 6 7)))

