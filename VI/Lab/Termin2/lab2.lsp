;gnu clisp  2.49.60


(defun minpom (listarg)
    (if (null listarg) '();then
        ;else
        (if (listp listarg)
            ;then - arg is list
            (if (null (car listarg)) '() ;then
                ;else
                (if (null (cdr listarg)) (car listarg) ; then
                    ;else
                    (if (< (minpom (car listarg))(minpom (cdr listarg)))
                        ;then
                        (minpom (car listarg))
                        ;else
                        (minpom (cdr listarg))
                        )
                    )
                )
            ;else - arg is atom
            listarg
        )
     )
)

(print (minpom '((3 6) 6 (2 (3 4) 1) 8 9)))

(defun list_oduzimanje (list1 list2)
    (if (and (null list1) (null list2)) '();then
        ;else
        (if (null list1) (cons (- 0 (car (reverse list2))) 
                               (list_oduzimanje list1 (reverse (cdr (reverse list2)))));then
            ;else
            (if (null list2) (cons (car list1) 
                               (list_oduzimanje list1 list2));then
                ;else
                (cons (- (car list1) (car (reverse list2))) 
                               (list_oduzimanje (cdr list1) (reverse (cdr (reverse list2)))))
             )
            )
     )
    )

(print (list_oduzimanje '(4 5 6) '(1 2 3)))