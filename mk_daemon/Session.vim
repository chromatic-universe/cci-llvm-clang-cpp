let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +159 /dev_src/daemon/src/chromatic_daemon.cpp
badd +0 /dev_src/mk_daemon/chromatic-daemon
badd +5 /dev_src/mk_daemon/chromatic_daemon.cpp
badd +7 /dev_src/mk_daemon/main.cpp
badd +0 /dev_src/mk_daemon/include/chromatic_daemon.h
silent! argdel *
set lines=51 columns=224
winpos 0 0
edit /dev_src/mk_daemon/chromatic_daemon.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 31 + 112) / 224)
exe '2resize ' . ((&lines * 26 + 25) / 51)
exe 'vert 2resize ' . ((&columns * 151 + 112) / 224)
exe '3resize ' . ((&lines * 17 + 25) / 51)
exe 'vert 3resize ' . ((&columns * 151 + 112) / 224)
exe 'vert 4resize ' . ((&columns * 40 + 112) / 224)
argglobal
enew
file ~/NERD_tree_1
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal nofen
wincmd w
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 24 - ((23 * winheight(0) + 13) / 26)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
24
normal! 0
wincmd w
argglobal
edit /dev_src/mk_daemon/include/chromatic_daemon.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 33 - ((2 * winheight(0) + 8) / 17)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
33
normal! 09|
wincmd w
argglobal
enew
file /dev_src/mk_daemon/__Tagbar__
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal nofen
wincmd w
4wincmd w
exe 'vert 1resize ' . ((&columns * 31 + 112) / 224)
exe '2resize ' . ((&lines * 26 + 25) / 51)
exe 'vert 2resize ' . ((&columns * 151 + 112) / 224)
exe '3resize ' . ((&lines * 17 + 25) / 51)
exe 'vert 3resize ' . ((&columns * 151 + 112) / 224)
exe 'vert 4resize ' . ((&columns * 40 + 112) / 224)
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
