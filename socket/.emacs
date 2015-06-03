;; This file is designed to be re-evaled; use the variable first-time
;; to avoid any problems with this.
(defvar first-time t
  "Flag signifying this is the first time that .emacs has been evaled")

(setq line-number-mode t)
(setq column-number-mode t)
(setq compilation-auto-jump-to-first-error t)
;;(setq x-select-enable-clipboard t)


(add-to-list 'load-path "~/.emacs.d/evil-evil")
(require 'evil)
(evil-mode 1)

;(key-chord-define-global "JJ" 'switch-to-previous-buffer)
(global-set-key (kbd "C-c o") 'switch-to-previous-buffer)
;(global-set-key (kbd "C-c p") 'other-window)
;; Meta
;(global-set-key "\M-," 'set-mark-command)
(global-set-key "\M-," 'ibuffer)
;;dd(global-set-key "\C-x-c," 'kill-ring-save)
(global-set-key "\M-\C-h" 'backward-kill-word)
(global-set-key "\M-\C-r" 'query-replace)
(global-set-key "\M-r" 'replace-string)
(global-set-key "\M-g" 'goto-line)
(global-set-key "\M-h" 'help-command)
;(global-set-key "\C-o" 'pop-global-mark)
;; Function keys
(global-set-key [f6] 'linum-mode)

(global-set-key [f2] 'info)
(global-set-key [f3] 'repeat-complex-command)
(global-set-key [f4] 'advertised-undo)
(global-set-key [f5] 'eval-current-buffer)
(global-set-key [f5] 'pop-global-mark)
;(global-set-key [f6] 'buffer-menu)
;(global-set-key [f7] 'other-window)
(global-set-key [f8] 'find-file)
(global-set-key [f9] 'save-buffer)
(global-set-key [f10] 'next-error)
(global-set-key [f11] 'compile)
(global-set-key [f12] 'grep)
(global-set-key [C-f1] 'compile)
(global-set-key [C-f2] 'grep)
(global-set-key [C-f3] 'next-error)
(global-set-key [C-f4] 'previous-error)
(global-set-key [C-f5] 'display-faces)
(global-set-key [C-f8] 'dired)
(global-set-key [C-f10] 'kill-compilation)

; ffap
(setq frame-title-format 
   '(:eval (if (buffer-file-name) (abbreviate-file-name(buffer-file-name)) "%b")))
;(buffer-name)
;M-: default-directory   dired-directory
(require 'uniquify)
(setq uniquify-buffer-name-style 'forward)
;(shell-command "grep -nH 'setq' ~/.emacs" 1)


(defun switch-to-previous-buffer ()
  "Switch to previously open buffer.
Repeated invocations toggle between the two most recently open buffers."
  (interactive)
  (switch-to-buffer (other-buffer (current-buffer) 1)))

(require 'ibuffer)

(setq ibuffer-saved-filter-groups
      (quote (("default"
               ("dired" (mode . dired-mode))
               ("java" (mode . java-mode))
               ("org" (mode . org-mode))
               ("sql" (mode . sql-mode))
               ("xml" (mode . nxml-mode))))))    

(setq ibuffer-show-empty-filter-groups nil)

(add-hook 'ibuffer-mode-hook 
 (lambda () 
  (ibuffer-switch-to-saved-filter-groups "default")
  (ibuffer-filter-by-filename "."))) ;; to show only dired and files buffers



;(evil-set-initial-state 'term-mode 'insert)
;(evil-set-initial-state 'shell-mode 'insert)

   (defun add-mode-line-dirtrack ()
      (add-to-list 'mode-line-buffer-identification 
                   '(:propertize (" " default-directory " ") face dired-directory)))
    (add-hook 'shell-mode-hook 'add-mode-line-dirtrack)

(defun find-file-at-point-with-line()
  "if file has an attached line num goto that line, ie boom.rb:12"
  (interactive)
  (setq line-num 0)
  (save-excursion
    (search-forward-regexp "[^ ]:" (point-max) t)
    (if (looking-at "[0-9]+")
         (setq line-num (string-to-number (buffer-substring (match-beginning 0) (match-end 0))))))
  (find-file-at-point)
  (if (not (equal line-num 0))
      (goto-line line-num)))

;;;;;;;;;
    (setq line-num (string-to-number (match-string 1))) 
    (if (looking-at "[0-9]+")
         (setq line-num (string-to-number (buffer-substring (match-beginning 0) (match-end 0)))))
   ;)
     (message"hello, %d" line-num)
)
 ; (find-file-at-point)
  ;(if (not (equal line-num 0))
   ;   (goto-line line-num)))
(message (regexp-quote (match-string 1))) 
     
    (re-search-forward "\\(/.*\\)\t\\([0-9]+\\)" (point-max) t)
     (message (match-string 1)) 
     (find-file-at-point  (match-string 1))


;;;;;;;;;;

(defun a-test-func()
  "if file has an attached line num goto that line, ie boom.rb:12"
  (interactive)
  (setq line-num 0)
  (save-excursion
    ;(re-search-forward "/.*\t\\([0-9]+\\)" (point-max) t)
    (beginning-of-line)
    (re-search-forward "\\(/.*\\)\t\\([0-9]+\\)" (point-at-eol) t)
   )  
      (if (match-string 2)
        (setq line-num (string-to-number (match-string 2))) 
      )
     (if (match-string 1)
      ;(find-file-at-point  (match-string 1))
      (find-file-other-window  (match-string 1))
     )
       (if (not (equal line-num 0))
      (goto-line line-num)))
     
TclREJECTind	/home/guolili/ttcn_3306/MME_SGSN_tester/ttcn3libs/asn/TCAP.asn	334;"	f
