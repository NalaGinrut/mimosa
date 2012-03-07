;;  Copyright (C) 2012  
;;  "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>

;;  This program is free software: you can redistribute it and/or modify
;;  it under the terms of the GNU General Public License as published by
;;  the Free Software Foundation, either version 3 of the License, or
;;  (at your option) any later version.

;;  This program is distributed in the hope that it will be useful,
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;  GNU General Public License for more details.

;;  You should have received a copy of the GNU General Public License
;;  along with this program.  If not, see <http://www.gnu.org/licenses/>.

(define-module (mimosa isr)
  #:export (get-isr-wrapper
	    get-isr-header
	    make-isr-define-help
	    isr-def?)
  )

(define header-list
  '((pc32 ".align 4\n")
    ))

(define (get-isr-header arch)
  (car (assoc-ref header-list 'pc32)))

(define wrapper-list
  '((pc32 ".globl __real_~a_isr\n__real_~a_isr:
           pusha
           call  ~a
           popa
           iret\n\n")
    ;; add other platform wrapper
    ))

(define (make-isr-wrapper arch)
  (lambda (isr)
    (let ([w (car (assoc-ref wrapper-list arch))])
      (format #f w isr isr isr))))

(define *isr-wrapper-table*
  `((pc32 ,(make-isr-wrapper 'pc32))
    ;; add other platform wrapper
    ))

(define (get-isr-wrapper arch)
  (car (assoc-ref *isr-wrapper-table* (string->symbol arch))))

(define (make-isr-define-help arch)
  (lambda (isr)
    ((get-isr-wrapper arch) isr)))

(define (isr-def? str) 
  (and (> (string-length str) 7)
       (string=? (substring str 0 7) "@isrdef")))
