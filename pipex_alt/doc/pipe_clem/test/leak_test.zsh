#!/zsh

echo "==========Compare Leaks======================"
echo ""
echo "          [correct]"
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all ./pipex test/in "cat -e" "wc -l" test/out;
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all < test/in cat -e | wc -l > test/out;
echo ""

echo "          [wrong file1]"
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all ./pipex XX "cat -e" "wc -l" test/out;
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all < XX cat -e | wc -l > test/out;
echo ""

echo "          [wrong cmd1]"
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all ./pipex test/in "XX" "echo "salut"" test/out;
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all < test/in XX | echo "salut" > test/out;
echo ""

echo "          [wrong cmd2]"
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all ./pipex test/in "echo "salut"" "XX" test/out;
echo ""
valgrind -q --leak-check=yes --show-leak-kinds=all < test/in echo "salut" | XX > test/out;

# echo "          [wrong cmd2 with cat -e]"
# echo ""
# valgrind -q --leak-check=yes --show-leak-kinds=all ./pipex test/in "cat" "XX" test/out
# echo ""
# valgrind -q --leak-check=yes --show-leak-kinds=all < test/in cat | XX > test/out
# echo ""

# echo "          [wrong cmd2 with ls]"
# echo ""
# valgrind -q --leak-check=yes --show-leak-kinds=all ./pipex test/in "ls" "XX" test/out; cat -e test/out
# echo ""
# valgrind -q --leak-check=yes --show-leak-kinds=all < test/in ls | XX > test/out; cat -e test/out
# echo ""
# echo "============================================="
