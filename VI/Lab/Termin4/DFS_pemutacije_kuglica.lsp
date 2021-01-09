;gnu clisp  2.49.60

; Definicija problema:
; Neka je lista sa kuglicama lista celih brojeva (boje: crvena - 1, zelena - 2, žuta - 3, plava - 4)
; Lista može da ima samo elemente 1, 2, 3, 4
; Lista je konačna
; 
;Parametri za unos:           pozicija - lista sa kuglicama
;                             N - određuje broj boja (ako ima 3 boje)
;
; Rezultat: Lista poteza koji dovode do ciljnog stanja

; vraća t - ako je ispravan redosled kuglica '() - ako nije
; N - poslednja boja kuglice, element - vrednost poslednje kuglice, pozicija - lista neobrađenih kuglica
(defun ciljp (pozicija element N)
    (cond
        ; case pozicija == null
        ((null pozicija) (if (eql element N) t;then
                               ;else
                               '()
                               )
                           )
        ; case element na mestu
        ((or (eql element (car pozicija)) 
             (eql (+ element 1) (car pozicija))
             )
         (ciljp (cdr pozicija) (car pozicija) N)
         )
        ; default-case element neispravan
        (t '())
     )
    )

(defun uporedilistep (lista1 lista2)
    (if (and (null lista1) (null lista2)) t;then
        ;else
        (if (or (null lista1) (null lista2)) '();then
            ;else
            (if (eql (car lista1) (car lista2)) (uporedilistep (cdr lista1) (cdr lista2));then
                ;else
                '()
                )
            )
        )
    )

; provera da li cvor(pozicija) postoji u listi
(defun cvorexistp (cvor cvorovi)
    (if (null cvorovi) '();then
        ;else
        (if (uporedilistep cvor (car cvorovi)) t;then
            ;else
            (cvorexistp cvor (cdr cvorovi))
            )
     )
    )

; proverava generisane pozicije nove pozicije
(defun novi-cvorovi (potomci cvorovi)
    (cond ((null potomci) '()); case 0: ako nema više potomaka povratak
        ; case 1: ako postoji u listi prelazak na sledeći
        ((cvorexistp (car potomci) cvorovi) 
         (novi-cvorovi (cdr potomci) cvorovi) 
         )
        ; case 2: ako ne postoji znači da nije pre viđen dodaje se u listu
        (t (cons (car potomci)
                 (novi-cvorovi (cdr potomci) cvorovi)
                 )
           )
        )
    )

; f-ja vraća sve permutacije
(defun dodaj-potomke-recursive (cvor)
    (cond ((null cvor) '()); case 0: prazna lista ne utiče na rezultat (sve elemente smo obradili)
        ; case 1: ostao je jedan element ne utiče na rezultat
        ((eql (length cvor) '1) (list cvor))
        ; case 2: ostala su dva elementa postoje dve permutacije, vraćamo drugu
        ((eql (length cvor) '2) (if (< (nth 1 cvor) (nth 0 cvor)) (list(reverse cvor)) (list cvor)))
        ; default case: ostalo je više elemenata permutacija se vrši između 2. element se pomera levo i desno
        (t (append 
            
            (if (< (nth 1 cvor) (nth 0 cvor))
                ;then
                (list (cons (nth 1 cvor) (cons (nth 0 cvor) (cddr cvor)))); prvi i drugi menjaju mest
                ;else
                '()
                )
            
            (if (< (nth 2 cvor) (nth 1 cvor))
                ;then
                (list (cons (nth 0 cvor) (cons(nth 2 cvor) (cons (nth 1 cvor) (cdddr cvor))))); drugi i treći menjaju mesta
                ;else
                '()
                )
                  (mapcar (lambda (x) (cons (nth 0 cvor) 
                                            (cons (nth 1 cvor) x)
                                            )
                                  )
                          (dodaj-potomke-recursive (cddr cvor))
                          )
            )
           )
        )
    )

; cvor - čvor za koji tražimo potomke, cvorovi - lista obiđenih, n - potez
; f-ja vraća samo permutacije koje ranije nisu viđene
(defun dodaj-potomke (cvor cvorovi)
    (novi-cvorovi (dodaj-potomke-recursive cvor); potomci
                  cvorovi
                  )
    )

; rezultat - putanja, N - broj boja, cvorovi - čvorovi koji su već obrađeni, red - neobrađeni čvorovi
(defun modifieddfs (N cvorovi red)
    (cond
        ; case 0: nema više čvorova za obradu (ne postoji rešenje)
        ((null red) '())
        ;case 1: nađen je ciljni čvor
        ((ciljp (car red) '0 N) (car red))
        ; default case: obrada čvora
        (t (let* ((cvorovipom (cons (car red) cvorovi)); nova lista obrađenih čvorova
                  (potomci (dodaj-potomke (car red) (append (cdr red) cvorovipom))); potomci tekućeg čvora
                  ; dodavanje u red (DFS, stavlja se na početak)
                  (redpom (append  potomci (cdr red)))
                  ; pamćenje putanje
                  (put (modifieddfs N cvorovipom redpom))
                  )
                 ;(cond
                     ; case 0: nema rešenja (greška)
                     ;((null put) '())
                     ; case 1: potomci tekućeg su deo puta, onda je i on deo puta (dodaje se na početak)
                     ;((cvorexistp (car put) potomci))
                     ; default case: tekući nije deo puta
                     ;(t put)
                     ;)
                 ;)
                 (append (car red) put)
                 )
           )
     )
    )

(defun modifieddutchflaginlisp (pozicija N)
    (if (or (null pozicija) (>= '0 N)) '();then
        ;else
        (modifieddfs N '() (list pozicija))
        )
    )


;lp – lista elemenata koje treba štampati
;i – iterator (početna vrednost 0)
;n – broj elemenata liste koje treba štampati u istom redu
(defun stampa (i n lp)
 (cond ((null lp) '())
 ((equal i n) (progn (format t "~%") (stampa 0 n lp)))
 (t (progn (format t "~a " (car lp)) (stampa (1+ i) n (cdr lp))))
     )
    )


(setq test '(2 1 3 1 2 3 3 1 2 2 1 3))
(setq test2 '(2 4 1 4 3 1 2 4 3 3 4 1 2 2 1 3))
(setq test3 '(5 2 4 5 1 4 3 1 2 4 3 5 3 4 1 2 2 1 3 5))

;(trace modifieddfs)
;(trace dodaj-potomke-recursive)
;(trace novi-cvorovi)
;(trace cvorexistp)
;(trace cons)
;(trace ciljp)

(stampa '0 '20 (modifieddutchflaginlisp test '3))
(format t "~%")
(format t "~%")
(stampa '0 '20 (modifieddutchflaginlisp test2 '4))
(format t "~%")
(format t "~%")
(stampa '0 '20 (modifieddutchflaginlisp test3 '5))