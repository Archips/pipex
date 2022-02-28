#!/zsh

echo "==========Compare Output====================="

echo "          [correct]"
./pipex test/in "cat -e" "wc -l" test/out; echo -n "out="; cat -e test/out
< test/in cat -e | wc -l > test/out; echo -n "out="; cat -e test/out

echo "          [wrong file1]"
./pipex XX "cat -e" "wc -l" test/out; echo -n "out="; cat -e test/out
< XX cat -e | wc -l > test/out; echo -n "out="; cat -e test/out

echo "          [wrong cmd1]"
./pipex test/in "XX" "echo "salut"" test/out; echo -n "out="; cat -e test/out
< test/in XX | echo "salut" > test/out; echo -n "out="; cat -e test/out

echo "          [wrong cmd2]"
./pipex test/in "echo "salut"" "XX" test/out; echo "out="; cat -e test/out
< test/in echo "salut" | XX > test/out; echo "out="; cat -e test/out

echo "============================================="
