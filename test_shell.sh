#!/bin/bash
# Script de test pour minishell2

# Initialiser les compteurs
success_count=0
fail_count=0
# Compteur de returns
return_count=0
return_failed=0

echo "=== Début des tests de minishell2 ==="

# Créer des fichiers temporaires pour les tests
echo "Contenu pour test de redirection" > test_input.txt
echo "Ligne 1" > test_multiline.txt
echo "Ligne 2" >> test_multiline.txt
echo "Ligne 3" >> test_multiline.txt

# Création des dossiers d'outputs
mkdir -p tests_outputs/mysh
mkdir -p tests_outputs/tcsh

# Fonction pour exécuter un test
run_test() {
    MYSH=tests_outputs/mysh/$4
    TCSH=tests_outputs/tcsh/$4

    echo -e "\n--- Test: $1 ---"
    echo "Commande: $2"
    # Capture le code de retour de ./mysh
    echo "$2" | ./mysh > "$MYSH" 2>&1
    mysh_ret=$?
    echo "$2" | tcsh > "$TCSH" 2>&1
    tcsh_ret=$?
    if [ $mysh_ret -eq $tcsh_ret ]; then
        echo "✅ Return code correct"
        ((return_count++))
    else
        echo "❌ Return code incorrect"
        echo "Return code attendu: $tcsh_ret"
        echo "Return code obtenu: $mysh_ret"
        ((return_failed++))
    fi
    echo "Comparaison des sorties:"
    if cmp -s "$MYSH" "$TCSH"; then
        echo "✅ Sortie similaire : test réussi"
        ((success_count++))
    else
        echo "❌ Sortie différentes : test échoué"
        echo "Sortie MYSH: $MYSH"
        echo "Sortie TCSH: $TCSH"
        echo "Différences:"
        diff "$MYSH" "$TCSH"
        ((fail_count++))
    fi
}

# Test de commandes simples
run_test "Commande simple" "ls -l" "0" "01"
run_test "Commande intégrée" "pwd" "0" "02"

# Test de pipes
run_test "Pipe simple" "ls | wc -l" "0" "03"
run_test "Pipe multiple" "ls | grep .c | wc -l" "0" "04"

# Test de redirections
run_test "Redirection sortie >" "ls > test_output.txt" "0" "05"
run_test "Vérification redirection sortie" "cat test_output.txt" "0" "06"
run_test "Redirection entrée <" "cat < test_input.txt" "0" "07"
run_test "Redirection append >>" "echo \"append test\" >> test_output.txt" "0" "08"
run_test "Vérification append" "cat test_output.txt" "0" "09"

# Test de combinaison de redirections et pipes
run_test "Pipe avec redirection" "ls | grep .c > test_c_files.txt" "0" "10"
run_test "Vérification pipe+redirection" "cat test_c_files.txt" "0" "11"

# Test de séparateurs de commandes
run_test "Séparateur de commandes" "ls ; pwd" "0" "12"
run_test "Séparateur avec pipe" "ls | wc -l ; pwd" "0" "13"

echo -e "\n=== Tests du fichier 'tests' ==="

# Test 901: Nothing
echo -e "\n--- Test 901: Nothing ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "Commande vide" "" "0" "901"

# Test 902: Exec two command
echo -e "\n--- Test 902: Exec two command ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "ls /etc" "ls /etc" "0" "902"
run_test "cat /etc/resolv.conf" "cat /etc/resolv.conf" "0" "902"

# Test 903: Testing with /usr/bin PATH
echo -e "\n--- Test 903: Testing with /usr/bin PATH ---"
export TERM=xterm
PATH='/usr/bin'
run_test "pwd avec PATH=/usr/bin" "pwd" "0" "903"

# Test 904: Testing with /bin PATH
echo -e "\n--- Test 904: Testing with /bin PATH ---"
export TERM=xterm
PATH='/bin'
run_test "pwd avec PATH=/bin" "pwd" "0" "904"

# Test 905: run commands
echo -e "\n--- Test 905: run commands ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "cat /etc/resolv.conf" "cat /etc/resolv.conf" "0" "905"
sleep 0.5
run_test "ls -l /etc" "ls -l /etc" "0" "905"
sleep 0.5
run_test "pwd" "pwd" "0" "905"

# Test 906: setenv and unsetenv
echo -e "\n--- Test 906: setenv and unsetenv ---"
/usr/bin/env > .lstenv
while read varenv ; do unset $varenv ; done < <(/bin/cat .lstenv | /usr/bin/cut -f1 -d=)
export PATH=/bin:/usr/bin
export _=ls
export LS_COLORS=RID
export MYBG=4
export LVL=4
export NOTE=2

run_test "unsetenv HOSTTYPE" "unsetenv HOSTTYPE" "0" "906"
run_test "unsetenv VENDOR" "unsetenv VENDOR" "0" "906"
run_test "unsetenv OSTYPE" "unsetenv OSTYPE" "0" "906"
run_test "unsetenv MACHTYPE" "unsetenv MACHTYPE" "0" "906"
run_test "unsetenv SHLVL" "unsetenv SHLVL" "0" "906"
run_test "unsetenv PWD" "unsetenv PWD" "0" "906"
run_test "unsetenv LOGNAME" "unsetenv LOGNAME" "0" "906"
run_test "unsetenv USER" "unsetenv USER" "0" "906"
run_test "unsetenv GROUP" "unsetenv GROUP" "0" "906"
run_test "unsetenv HOST" "unsetenv HOST" "0" "906"
run_test "unsetenv REMOTEHOST" "unsetenv REMOTEHOST" "0" "906"
run_test "unsetenv _" "unsetenv _" "0" "906"
run_test "unsetenv LS_COLORS" "unsetenv LS_COLORS" "0" "906"
run_test "unsetenv NOTE" "unsetenv NOTE" "0" "906"
run_test "setenv titi" "setenv titi" "0" "906"
run_test "setenv tata coucou" "setenv tata coucou" "0" "906"
run_test "env" "env" "0" "906"
run_test "/usr/bin/env" "/usr/bin/env" "0" "906"
run_test "setenv var1 val1" "setenv var1 val1" "0" "906"
run_test "setenv var2 val2" "setenv var2 val2" "0" "906"

# Nettoyage pour test 906
while read varenv ; do export "$varenv" 2>/dev/null ; done < <(/bin/cat .lstenv)
/bin/rm -f .lstenv

# Test 907: builtin cd
echo -e "\n--- Test 907: builtin cd ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "cd .." "cd .." "0" "907"
run_test "ls -l" "ls -l" "0" "907"
run_test "cd /usr" "cd /usr" "0" "907"
run_test "ls -l" "ls -l" "0" "907"

# Test 908: many tab and space
echo -e "\n--- Test 908: many tab and space ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "tabs and spaces" "		    ls	     	-l    		  	 -a /usr   		" "0" "908"

# Test 909: Launch DivZero program with core dump
echo -e "\n--- Test 909: Launch DivZero program with core dump ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "Division par zéro" "./my_divzero" "127" "909"

# Test 910: Launch SegFault program without core dump
echo -e "\n--- Test 910: Launch SegFault program without core dump ---"
ulimit -c 0
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "Segmentation fault" "./segfault" "139" "910"

# Test 911: Testing simple pipe
echo -e "\n--- Test 911: Testing simple pipe ---"
export TERM=xterm
PATH='/bin:/usr/bin'
run_test "Pipe simple grep" "ls -l /etc | grep sh" "0" "911"

# # Test 912: A pipe with a builtin ?
# echo -e "\n--- Test 912: A pipe with a builtin ? ---"
# export VAR1=VALEUR1
# OLDPATH=$PATH
# PATH='/random'
# run_test "setenv | grep" "setenv | /bin/grep VAR1" "0" "912"
# run_test "ls | cd" "/bin/ls | cd /usr" "0" "912"
# run_test "ls -l" "ls -l" "0" "912"
# # run_test "exit | cat" "exit 45|cat /etc/resolv.conf" "0" "912"
# PATH=$OLDPATH

# # Nettoyage
# run_test "Nettoyage" "rm test_input.txt test_output.txt test_multiline.txt test_c_files.txt" "0" "999"

echo "=== Fin des tests ==="
echo -e "\n=== Résumé des tests ==="
echo "✅ Sortie réussis: $success_count"
echo "❌ Sortie échoués: $fail_count"
echo "✅ Return code réussis: $return_count"
echo "❌ Return code échoués: $return_failed"
echo -e "\n=== Totals des tests ==="
echo "✅Tests réussis: $((success_count + return_count))"
echo "❌Tests échoués: $((fail_count + return_failed))"
echo "Total des tests: $((success_count + fail_count + return_count + return_failed))"