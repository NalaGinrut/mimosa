;;  Copyright (C) 2011  "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>

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



(define-module (mimosa config)
  #:use-module (mimosa sxml)
  #:use-module (sxml xpath)
  #:use-module (oop goops)
  #:use-module (ice-9 getopt-long)
  #:use-module (ice-9 match)
  
  #:export (<config>
	    config:gen-memlayout
	    config:gen-osconfig
	    config:gen-ldconfig
	    config:gen-mkconfig
	    )
  )

(define-class <config> ()
  (work-list #:init-value '())
  (mem-layout #:init-value '())
  (page-setup #:init-value '())
  (sxml #:init-value #f)
  (init #:accessor config:init
	#:allocation #:virtual
	#:slot-set! (lambda (o v) #f)
	#:slot-ref 
	(lambda (o)
	  (let* ((sxml (make <sxml>)) 
		 (cache '())
		 )
	    (sxml:read sxml "config/config.xml")
	    (slot-set! o 'sxml sxml)
	    )))
  )


(define gen-code-list 
  (lambda (entry)
    (lambda (sxml)
      (let* ((conf-list (make-conf-list sxml entry))
	     (code-list '()) 
	     )
	(for-each (lambda (x)
		    (if (pair? x) 
			(set! code-list
			      (cons
			       (format #f "#define ~a ~a"
				       (car x) (cadr x))
			       code-list))))
		  conf-list
		  )
	(set! sxml entry code-list)
	))))

(define config:gen-memlayout
  (gen-code-list 'memlayout))

(define config:gen-osconfig
  (gen-code-list 'osconfig))

(define config:gen-ldconfig
  (gen-code-list 'ldconfig))

(define config:gen-mkconfig
  (gen-code-list 'mkconfig))

(define get-attr-value
  (lambda (conf-list-item)
    (match conf-list-item
	   ((name (@ (attribute value)) data))
	   )
    )
  )

(define make-conf-list
  (lambda (sxml entry)
    (cdar ((sxpath `(,entry)) sxml))))
      

       
(define number-to-hex-string
  (lambda (number)
    (format #t "0x~a" (number->string number 16))
    )
  )
