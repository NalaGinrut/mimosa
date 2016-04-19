#! /usr/local/bin/guile \
-L ./scripts -e main
!#

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

(use-modules (mimosa isr)
	     (mimosa conf)
	     (ice-9 rdelim)
	     (rnrs io ports))

(define main
  (lambda args
    (cond
     ((not (= (length (car args)) 2))
      (format #t "usage: ~a [arch]~%" (caar args)))
     (else
      (let* ([arch (cadar args)]
	     [fp (open-input-file isr-path)]
	     [wrapper (make-isr-define-help arch)]
	     [h (get-isr-header arch)]
	     )
	(format #t "~a~%" (get-string-all (open-input-file hfg)))
	(format #t "~a~%" h)
	(let lp([rd (read-line fp)])
	  (cond
	   ((eof-object? rd)
	    (primitive-exit))
	   ((isr-def? rd)
	    (let* ([ll (string-split rd #\space)]
		   [isr (cadr ll)]
		   )
	      (display (wrapper isr))
	      (lp (read-line fp))))
	   (else
	    (lp (read-line fp))
	    ))))))))
		
