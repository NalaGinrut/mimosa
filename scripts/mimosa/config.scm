;;  Copyright (C) 2016  "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>

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
  #:use-module (sxml simple)
  #:use-module (sxml xpath)
  #:use-module (ice-9 match)
  #:export (gen-osconfig))

(define (get-from path key)
  (lambda (sxml)
    (and=> (assoc-ref (assoc-ref ((sxpath path) sxml)
                                 (list-ref path (1- (length path))))
                      key)
           car)))

(define platform '(config platform))
(define platform-name (get-from platform 'name))
(define platform-bitwidth (get-from platform 'bitwidth))

(define memory '(config memory))
(define memeory-kernbase (get-from memory 'kern_base))
(define memory-kernstack (get-from memory 'kern_stack))
(define memory-kernbegin (get-from memory 'kern_begin))
(define memory-fulladdr (get-from memory 'full_addr))

(define page '(config mmu page))
(define page-enabled (get-from page 'enabled))
(define page-ptlevel (get-from page 'pt_level))
(define page-pgsize (get-from page 'pg_size))
(define page-pgentries (get-from page 'pg_entries))
(define page-ptsize (get-from page 'pt_size))
(define page-pdsize (get-from page 'pd_size))

(define boot '(config boot))
(define boot-grub (get-from boot 'grub))

(define (num->hex num) (format #f "0x~x" num))

(define (->bool str)
  (let ((s (string-downcase str)))
    (cond
     ((string=? "true" s) #t)
     ((string=? "false" s) #f)
     (else (error ->bool "Invalid value!" str)))))

(define (gen-osconfig bsp)
  (let* ((conf (format #f "config/platforms-xml/~a.xml" bsp))
         (sxml (call-with-input-file conf
                 (lambda (port) (xml->sxml port #:trim-whitespace? #t)))))
    (when (->bool (boot-grub sxml)) (format #t "#define __MULTI_BOOT__~%"))
    (format #t "#define MIMOSA_BSP ~s~%" (platform-name sxml))
    (format #t "#define FULL_ADDR ~a~%" (platform-fulladdr sxml))

    (when (->bool (page-enabled sxml))
          (format #t "#define PT_LEVEL ~a~%" (page-ptlevel sxml))
          (format #t "#define PG_SIZE ~a~%" (page-pgsize sxml))
          (format #t "#define PG_ENTRIES ~a~%" (page-pgentries sxml))
          (format #t "#define PT_SIZE ~a~%" (page-ptsize sxml))
          (format #t "#define PD_SIZE ~a~%" (page-pdsize sxml)))

    (when (->bool (boot-grub sxml))
          (format #t "#define __MULTI_BOOT__~%"))
    ))
