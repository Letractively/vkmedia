# Introduction #

Vim editor code style settings.


# Details #

Settings:

if exists("b:did\_indent")
> finish
endif
let b:did\_indent = 1


function! GoogleCppIndent()
> let l:cline\_num = line('.')

> let l:orig\_indent = cindent(l:cline\_num)

> if l:orig\_indent == 0 | return 0 | endif

> let l:pline\_num = prevnonblank(l:cline\_num - 1)
> let l:pline = getline(l:pline\_num)
> if l:pline =~# '^\s\*template' | return l:pline\_indent | endif

> if l:orig\_indent != &shiftwidth | return l:orig\_indent | endif

> let l:in\_comment = 0
> let l:pline\_num = prevnonblank(l:cline\_num - 1)
> while l:pline\_num > -1
> > let l:pline = getline(l:pline\_num)
> > let l:pline\_indent = indent(l:pline\_num)


> if l:in\_comment == 0 && l:pline =~ '^.\{-}\(/\**.\{-}\)\@<!\**/'
> > let l:in\_comment = 1

> elseif l:in\_comment == 1
> > if l:pline =~ '/\**\(.\{-}\**/\)\@!'
> > > let l:in\_comment = 0

> > endif

> elseif l:pline\_indent == 0
> > if l:pline !~# '\(#define\)\|\(<sup>\s*//\)\|\(</sup>\s**{\)'
> > > if l:pline =~# '^\s\*namespace.**'
> > > > return 0

> > > else
> > > > return l:orig\_indent

> > > endif

> > elseif l:pline =~# '\\$'
> > > return l:orig\_indent

> > endif

> else
> > return l:orig\_indent

> endif

> let l:pline\_num = prevnonblank(l:pline\_num - 1)
> endwhile

> return l:orig\_indent
endfunction

setlocal shiftwidth=2
setlocal tabstop=2
setlocal softtabstop=2
setlocal expandtab
setlocal textwidth=80
setlocal wrap

setlocal cindent
setlocal cinoptions=h1,l1,g1,t0,i4,+4,(0,w1,W4

setlocal indentexpr=GoogleCppIndent()

let b:undo\_indent = "setl sw< ts< sts< et< tw< wrap< cin< cino< inde<"