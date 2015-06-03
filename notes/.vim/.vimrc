set paste
set nocompatible            " 关闭 vi 兼容模式
set number                  " 显示行号
noremap <C-C> "*y             
"noremap <C-C> "+y 
"noremap <C-Insert> "+y  
  
 " CTRL-V and SHIFT-Insert are Paste  
"noremap <C-V>        "+gP  
map <S-Insert>        "*gP 
let &termencoding=&encoding
set fileencodings=utf-8,gbk
"nmap  <silent> <F4> :vimgrep  ".expand("<cword>")<CR> i

set mouse=""
"set mouse=a
noremap <F4> <ESC> :execute ":lvimgrep  " .expand("<cword>"). "  **/*.cpp **/*.h **/*.hpp **/*.c"<CR><ESC>:lw<CR>

noremap <C-L> :ls<CR>
noremap <C-B> :bp<CR>
noremap <C-N> :bn<CR>
noremap B :make<CR><ESC>:copen<CR>
noremap C :cclose<CR>
set dictionary+=/usr/share/dict/words
set thesaurus+=~/.vim/thesaurus/mthesaur.txt
syntax on
au BufRead,BufNewFile *.ttcn            set filetype=ttcn
let mapleader=","
" Mappings to access buffers (don't use "\p" because a
" delay before pressing "p" would accidentally paste).
" \l       : list buffers
" \b \f \g : go back/forward/last-used
"" \1 \2 \3 : go to buffer 1/2/3 etc
"noremap <C-/>l :ls<CR>
"noremap <C-/>b :bp<CR>
"noremap \f :bn<CR>
"noremap <Leader>g :e#<CR>
"noremap <Leader>1 :1b<CR>
"noremap <Leader>2 :2b<CR>
"noremap <Leader>3 :3b<CR>
"nnoremap <Leader>4 :4b<CR>
"nnoremap <Leader>5 :5b<CR>
"nnoremap <Leader>6 :6b<CR>
"nnoremap <Leader>7 :7b<CR>
"nnoremap <Leader>8 :8b<CR>
"nnoremap <Leader>9 :9b<CR>
"nnoremap <Leader>0 :10b<CR>
" It's useful to show the buffer number in the status line.
set laststatus=2 statusline=%02n:%<%f\ %h%m%r%=%-14.(%l,%c%V%)\ %P

