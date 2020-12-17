(defun umetni (el n lista)
  (cond ((equal n 0) (append (list el) lista))
        (t (cons (car lista) (umetni el (- n 1) (cdr lista))))
      )
  )

(print (umetni 'd '3 '(a b c e f)))