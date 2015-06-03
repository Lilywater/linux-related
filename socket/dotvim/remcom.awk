BEGIN { FS="" }
{
  ignore_line = 0;
    for(i = 1; i <= NF; i++) {
        if (ignore_block) {
            if ($i $(i+1) == "*/") {
                ignore_block = 0
                i++ # remove '*'
            }
            continue
        }
        if (!ignore_block && $i $(i+1) == "/*") {
            ignore_block = 1
            i++ # remove '/'
            continue
        }
        if (!ignore_block && $i $(i+1) == "//") {
             ignore_line = 1
             i++
             continue
        }
         if (ignore_block || ignore_line)
           continue
     printf($i)
    }
    printf("\n")
}

