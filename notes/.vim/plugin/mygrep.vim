command! -nargs=* -complete=file J 
            \ call s:RunMyGrepCmd('setw','set',<f-args>)
command! -nargs=* -complete=file JJ 
            \ call s:RunMyGrepCmd('setw','add',<f-args>)
command! -nargs=* -complete=file Jw 
            \ call s:RunMyGrepCmd('word','set',<f-args>)
" RunGrepCmd()
" Run the specified grep command using the supplied cmd
"command! -nargs=* -complete=file Jw 
"            \ call s:RunMyGrepCmdWord(<f-args>)

command! -nargs=+ -complete=command G call s:RunMyCmd(<q-args>)
command! -nargs=+ -complete=file S call s:RunMyShellCmd(<q-args>)

command! -range -nargs=* -complete=command B :<line1>,<line2>call Block_process(<q-args>) 

command! OpEr :call OpenErrWin()

" Default grep current file 
if !exists("Grep_Default_Filelist")
    let Grep_Default_Filelist = '*'
endif

if !exists("Grep_Default_Word")
    let Grep_Default_Word = ''
endif


fun! Block_process(scmd) range
let alist = split( a:scmd ) 
let il = index(alist,'%')
if il > 0
  let sym=remove(alist,il)
  let cmd = join(alist)
 " let  g:curfn = bufname("%")
  "let cmd =  cmd  . " "  .  bufname("%") 
  exe   "new |read !" . cmd .   " "  . bufname("%") 
   return
endif


 if a:firstline == a:lastline
  exe 1 . "," . '$' . "w! /tmp/zzz"
 else
  exe a:firstline . "," . a:lastline . "w! /tmp/zzz"
 endif
"  echomsg "thisis type:" . type(a:scmd) 
" string 
 echomsg "thisis:" a:firstline 
  echomsg "sssss:" a:lastline 
  exe   "new |read !"  a:scmd   "/tmp/zzz" 
  se buftype=nowrite
 
 " save block for later use in variable
  " restore unnamed register
endfun


function! OpenErrWin()

  let  cmd =  "~/.vim/mj.sh 2>&1 |tee  erlog "
   let cmd_output = system(cmd)
 copen
" execute "lcd "  . roottesterpath . "/project"
 execute "cfile erlog" 

endfunction

function! s:RunMyCmd(cmd)
let alist = split( a:cmd ) 
let il = index(alist,'%')
if il > 0
  let clist = remove(alist,il)
   echo clist
  let cmd = join(alist)
  echomsg "index >0"
 " let  g:curfn = bufname("%")
  let cmd =  cmd  . " "  .  bufname("%") 
else
  let cmd =  a:cmd   
endif


let cmd_output =  system(cmd)          
"           echomsg "begin"  "and is" .  a:0 .  "end"
    if cmd_output == ""
        echohl WarningMsg | 
        \ echomsg "Error: cmd " . cmd . " not found" | 
        \ echohl None
        return
    endif

    let tmpfile = tempname()

    let old_verbose = &verbose
    set verbose&vim

    exe "redir! > " . tmpfile
    silent echon '[Search results for cmd: ' . cmd . "]\n"
    silent echon cmd_output
    redir END



    let &verbose = old_verbose

    let old_efm = &efm
    set efm=%f:%\\s%#%l:%m

    if v:version >= 700 "&& :action == 'add'
        execute "silent! lgetfile " . tmpfile
    else
        if exists(":lgetfile")
            execute "silent! lgetfile " . tmpfile
        else
            execute "silent! lfile " . tmpfile
        endif
    endif

    let &efm = old_efm

    " Open the grep output window
    " if g:Grep_OpenQuickfixWindow == 1
        " Open the quickfix window below the current window
        botright lopen
  "  endif



endfunction



function! s:RunMyGrepCmdWord(...)
 let argcnt = 1
 let cmd =  "grep -nH"
    while argcnt <= a:0
       "!echo  .  a:{argcnt}  .  >/tmp/mygrep
    "  echomsg "begin " . a:{argcnt} . " end"
  if argcnt == a:0
        
        let cmd =  cmd  . " " .  expand("<cword>") 
      if a:{argcnt} == '%'
       let cmd =  cmd  . " " .  bufname(%) 
      elseif a:{argcnt} == '+'
            let last_bufno = bufnr("$")
             let i = 1
             let filenames = ""
    "         let last_bufno
             while i <= last_bufno
                 if bufexists(i) && buflisted(i)
                     let filenames = filenames . "  " . bufname(i)
                 endif
                 let i = i + 1
            endwhile
     "       let filenames 
         let cmd =  cmd  . " " .  filenames
       else
        let cmd =  cmd  . " " .  a:{argcnt} 
       endif
    else
        let cmd =  cmd  . " " .  a:{argcnt} 
    endif
       let argcnt = argcnt + 1
       
    endwhile
" let  cmd 
 let cmd_output =  system(cmd)          
    if cmd_output == ""
        echohl WarningMsg | 
        \ echomsg "Error: cmd " . cmd . " not found" | 
        \ echohl None
        return
    endif


    let tmpfile = tempname()

    let old_verbose = &verbose
    set verbose&vim

    exe "redir! > " . tmpfile
    silent echon '[Search results for cmd: ' . cmd . "]\n"
    silent echon cmd_output
    redir END

    let &verbose = old_verbose

    let old_efm = &efm
    set efm=%f:%\\s%#%l:%m

        execute "silent! lg " . tmpfile
        let &efm = old_efm
        botright lopen
endfunction



function! s:RunMyGrepCmd(word,action,...)
 let argcnt = 0
 let cmd =  "grep -nH"
 let goptp = 0 
 let inc = 1 
    while argcnt <= a:0
       "!echo  .  a:{argcnt}  .  >/tmp/mygrep
     "    echomsg "begin " . argcnt . " end"
    if a:0 == argcnt
       if a:word == 'word' 
        if  expand("<cword>") != ""
         let g:Grep_Default_Word =  expand("<cword>")
        endif
        let cmd =  cmd  . " " .  g:Grep_Default_Word 
        let inc = 0 
       endif
      if argcnt == goptp + inc 
     "  echomsg "begin " . argcnt . " end"
        if bufname("%") != ""
         let  g:Grep_Default_Filelist = bufname("%")
        endif
        if argcnt != 0
          let cmd =  cmd  . " " .  a:{argcnt} . " " .  g:Grep_Default_Filelist 
        else 
          let cmd =  cmd  . " "  .  g:Grep_Default_Filelist 
        endif
      elseif a:{argcnt} == '+'
     " if a:{argcnt} == '+'
            let last_bufno = bufnr("$")
             let i = 1
             let filenames = ""
    "         let last_bufno
             while i <= last_bufno
                 if bufexists(i) && buflisted(i)
                     let filenames = filenames . "  " . bufname(i)
                 endif
                 let i = i + 1
            endwhile
     "       let filenames 
           if filenames != ""
            let  g:Grep_Default_Filelist = filenames
           endif
           let cmd =  cmd  . " " . g:Grep_Default_Filelist 
      else
       let cmd =  cmd  . " " .  a:{argcnt} 
      endif
   else 
      if argcnt != 0 
       let cmd =  cmd  . " " .  a:{argcnt} 
       if strpart(a:{argcnt},0,1) ==  "-"
          let goptp = argcnt          
        endif
      endif
   endif
       let argcnt = argcnt + 1
       
    endwhile
" let  cmd 
 let cmd_output =  system(cmd)          
    if cmd_output == ""
        echohl WarningMsg | 
        \ echomsg "Error: cmd " . cmd . " not found" | 
        \ echohl None
        return
    endif

    let tmpfile = tempname()

    let old_verbose = &verbose
    set verbose&vim

    exe "redir! > " . tmpfile
    silent echon '[Search results for cmd: ' . cmd . "]\n"
    silent echon cmd_output
    redir END

    let &verbose = old_verbose

    let old_efm = &efm
    set efm=%f:%\\s%#%l:%m
    if v:version >= 700 && a:action == 'add'
        execute "silent! laddfile " . tmpfile
    else
        execute "silent! lg " . tmpfile
    endif
   let &efm = old_efm
   botright lopen
    
endfunction

function! s:RunMyShellCmd(cmd)
"let cmd =  a:cmd  . " "  .  bufname("%") 

let alist = split( a:cmd ) 
let il = index(alist,'%')
if il > 0
  let clist = remove(alist,il)
   echo clist
  let cmd = join(clist)
  echomsg "index >0"
 " let  g:curfn = bufname("%")
  let cmd =  cmd  . " "  .  bufname("%") 
else
  let cmd =  a:cmd   
endif

  echomsg  cmd
let cmd_output =  system(cmd)          
"           echomsg "begin"  .   buffername("%") .  "end"

    if cmd_output == ""
        echohl WarningMsg | 
        \ echomsg "Error: cmd " . cmd . " not found" | 
        \ echohl None
        return
    endif

    let tmpfile = tempname()

    let old_verbose = &verbose
    set verbose&vim

    exe "redir! > " . tmpfile
    silent echon '[Search results for cmd: ' . cmd . "]\n"
    silent echon cmd_output
    redir END


    execute "silent! new " . tmpfile



endfunction



"    let cmd_output = system(a:cmd)
"

