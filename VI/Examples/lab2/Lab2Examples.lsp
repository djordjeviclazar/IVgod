;gnu clisp  2.49.60

(defun podelipom (divisor number pom) 
    (if (null number) '() ; then
         ;else
            (if (> divisor (car pom)) 
            ;then
                (cons (list 0) 
                      (podelipom divisor (cdr number) (+ (* 10 pom) (car number))))
            ;else
            ((cons (list (floor pom divisor)) 
                   (podelipom divisor (cdr number) (+ (* 10 (mod pom divisor)) (car number)))))
            )
     )
)

(defun podeli (divisor number); div operator
    (
        (if (null number) '() ; then
            ;else
            ((podelipom divisor (cdr number) (car number)));then
        )
     )
)

(print "Hello, world!")