;gnu clisp  2.49.60

; provera da li cvor postoji u listi elemenata oblika (cvor heuristika)
(defun cvorexistp (cvor cvorovi)
    (if (null cvorovi) '();then
        ;else
        (if (equal cvor (caar cvorovi)) t;then
            ;else
            (cvorexistp cvor (cdr cvorovi))
            )
     )
    )

;...
(defun novi-cvorovi (potomci cvorovi n)
    (cond ((null potomci) '()); ako nema više potomaka povratak
        ((cvorexistp (car potomci) cvorovi) 
         (novi-cvorovi (cdr potomci) cvorovi n) 
         ); ako postoji u listi prelazak na sledeći
        (t (cons (cons (car potomci) n)
                 (novi-cvorovi (cdr potomci) cvorovi n); 
                 )
           )
        )
    )

; graf, cvor - cvor čvor za koji tražimo potomke, cvorovi - lista obiđenih
(defun dodaj-potomke (graf cvor cvorovi)
    (cond ((null graf) '())
        ((equal (caar graf) (car cvor))
            (novi-cvorovi (cadar graf) cvorovi (+ (cdr cvor) 1))
         )
        (t (dodaj-potomke (cdr graf) cvor cvorovi))
        )
    )

; l lista neobrađenih čvorova čvor -> (ime heuristika)
; cvorovi lista obrađenih čvorova
(defun nadji-put (graf l cvorovi)
    (cond ((null l) cvorovi)
        ; nemamo ciljni čvor treba da se obiđu svi čvorovi
        (t (let* ((cvorovi1 (append cvorovi (list (car l))))
                  (potomci1 (dodaj-potomke graf (car l) (append (cdr l) cvorovi1)))
                  ;dodavanje u red (BFS)
                  (l1 (append (cdr l) potomci1))
                  )
                 (nadji-put graf l1 cvorovi1)
                 )
           )
        )
    )

(setq graf1 '((a (a b)) (b (c e)) (c (a b)) (d (e f)) (e (d)) (f (a))))
(setq graf2 '((a (b)) (b (c f)) (c (d)) (d (e)) (e (d)) (f (a))))
(setq graf3 '((a (a b)) (b (c e)) (c (b)) (d (e f)) (e (d)) (f (b))))
;(trace nadji-put)
;(trace dodaj-potomke)
;(trace novi-cvorovi)
;(trace cvorexistp)
(print (nadji-put graf1 '((a . 0)) '()))
(print (nadji-put graf1 '((c . 0)) '()))
(print (nadji-put graf3 '((d . 0)) '()))