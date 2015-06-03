if exists("did_load_filetypes") 
    finish 
endif 
augroup filetypedetect 
    au BufNewFile,BufRead *.ttcn  setf ttcn    << This is the line! 
    au BufNewFile,BufRead *.antlr setf antlr 
augroup END 


