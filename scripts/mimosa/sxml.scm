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



(define-module (mimosa sxml)
  #:use-module (sxml ssax)
  #:use-module (sxml xpath)
  #:use-module (sxml match)
  #:use-module (oop goops)
  #:use-module (web uri)

  #:export (<sxml>
	    sxml:get sxml:clear sxml:read
	    )
  )

(define-class <sxml> ()
  (namespace #:init-value #f #:accessor sxml:ns)
  (buffer #:init-value #f #:accessor sxml:buffer))

(define-generic sxml:read)
(define-generic sxml:clear)
(define-generic sxml:get)

(define-method (sxml:read (sxml <sxml>) (filename <string>))
  (let* ((ss (ssax:xml->sxml (open-file filename "r") '()))
	 (ns (get-namespace ss))
	 ) 
    (set! (sxml:buffer sxml) ss)
    (set! (sxml:ns sxml) ns)))

(define-method (sxml:clear (sxml <sxml>))
  (set! (sxml:buffer sxml) #f))

(define-method (sxml:get (sxml <sxml>) (names <string>))
  (let* ((ns (sxml:ns))
	 (tree (sxml:buffer))
	 )
    (get-sxml-node tree ns names)))


(define get-namespace
  (lambda (sxml)
    (let* ((tmp (symbol->string (caaddr sxml)))
	   (index (string-index-right tmp #\:))
	   )
      (if index
	  (string-copy tmp 0 index)
	  ""))))


(define get-sxml-node 
  (lambda (tree ns names)
    ((sxpath 
      (map 
       (lambda (x) (string->symbol (string-append ns ":" x)))
       (string-split names #\/)))
     tree)))

(define get-node-attribute
  (lambda (node ns names)
    (sxml-match
     node
     [(
