##for modifying the messages in log to a template format test.awk doing the main work
##cea {
#         sctpPrimitive {
#             associationId 1
#         }
#         version 1
#         msgLength 0
#         msgType answer(0)
#         proxiableMsg no(0)
#         errorMsg no(0)
 
set -x
if [ -z "$1"  ]
then
echo "the file name should be given"
exit
fi

sed 's/<< omit >>/omit/g' $1 | awk -f ~/.vim/test.awk | sed ' :a; N; s/,\n\([[:space:]]*\)}/\n\1}/g;ba' |sed 's/(.*)//' >$1.tn
