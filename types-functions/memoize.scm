(use-modules (srfi srfi-1)
	     (srfi srfi-13))

(define (factorial n)
  (memoizable-factorial memoizable-factorial n))


; continuation-passing style
(define (memoizable-factorial self n)
  (cond
   ((= n 0) 1)
   ((= n 1) 1)
   (else (+ (self self (- n 1)) (self self (- n 2))))))

; Regular memoize
(define (memoize f)
  (let ((storage (make-hash-table)))
    (lambda arg
      (let ((stored (hashq-ref storage arg)))
	(if (not stored)
	    (let ((result (f arg))) 
	      (hashq-set! storage arg result)
	      result)
	    stored)))))

(define (memoize-recursive f)
  (letrec ((storage (make-hash-table))
	(memoized (lambda (self arg)
		    (let ((stored (hashq-ref storage arg)))
		      (if (not stored)
			  (let ((result (f memoized arg)))
			    (hashq-set! storage arg result)
			    result)
			  stored)))))
    (lambda (arg)
      (memoized memoized arg))))
