;;  Copyright (C) 2012,2016,2018
;;      "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
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

(use-modules (ice-9 match))

(define (main args)
  (match args
    ((_ filename)
     (let ((fp (open-file filename "r+b")))
       (when (> (stat:size (stat filename)) 510)
         (format #t "File: ~s size is larger than 510B!~%" filename)
         (exit -1))
       (copy-file filename (string-append filename ".bak")) ;; A backup for debug
       (seek fp 510 SEEK_SET) ;; pad zero automatically
       (format fp "\x55\xAA") (close fp)
       (rename-file filename (string-append filename ".out"))
       (display "Seems the MBR has been generated successfully!!!\n")))
    (else
     (format #t "usage: ~a filename ~%" (car args)))))
