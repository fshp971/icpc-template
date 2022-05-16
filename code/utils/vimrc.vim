set si nu ts=4 sw=4 sts=4 mouse=a
syn on

func! Compile()
    if &filetype == 'c'
        :!gcc -g % -o %<.exe
    elseif &filetype == 'cpp'
        :!g++ -std=gnu++11 -g % -o %<.exe
    elseif &filetype == 'java'
        :!javac -g %
    elseif &filetype == 'php'
        :!php -l %
    endif
endfunc

func! Run()
    if &filetype == 'c'
        :!time ./%<.exe
    elseif &filetype == 'cpp'
        :!time ./%<.exe
    elseif &filetype == 'java'
        :!time java -cp %:p:h %:t:r
    elseif &filetype == 'python'
        :!time python3 %
    elseif &filetype == 'php'
        :!time php %
    endif
endfunc


map <F4> :call Compile()<cr>
map <F5> :call Run()<cr>
map <C-A> ggVG"+y
