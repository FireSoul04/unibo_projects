# Esercizio con Git, in locale

Per ogni passo,
si annoti in questo file il comando utilizzato ed il suo output,
per confrontarlo con le soluzioni.

### Si crei una nuova directory

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching ‹main›
╰─$ mkdir ex54

### Si inizializzi un repository Git dentro la cartella suddetta.

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching ‹main›
╰─$ cd ex54
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git init
Initialized empty Git repository in /home/davide/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54/.git/

### Si osservi lo stato del repository

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git status
On branch main

No commits yet

nothing to commit (create/copy files and use "git add" to track)

### Si scriva un file `HelloWorld.java` contenente un `main` con una stampa a video e si osservi il contenuto del repository

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ touch HelloWorld.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ vim HelloWorld.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        HelloWorld.java

nothing added to commit but untracked files present (use "git add" to track)

### Si aggiunga `HelloWorld.java` allo stage, e si osservi lo stato del repository

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git add HelloWorld.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   HelloWorld.java

### Si crei il primo commit, con messaggio ragionevole. Se necessario, si configuri nome utente ed email di git usando i dati dell'account istituzionale.

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git commit -m "Added HelloWorld class"
[main (root-commit) 8c860d3] Added HelloWorld class
 1 file changed, 5 insertions(+)
 create mode 100644 HelloWorld.java

### Si compili il file Java e si verifichi lo stato del repository

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ javac HelloWorld.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ java HelloWorld
Hello World!
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        HelloWorld.class

nothing added to commit but untracked files present (use "git add" to track)

### Si noti che c'è un file rigenerabile (`HelloWorld.class`). Si costruisca una lista di file ignorati che ignori tutti i file con estensione `.class`

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ echo "*.class" > .gitignore
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ cat .gitignore
*.class

### Si osservi lo stato del repository

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .gitignore

nothing added to commit but untracked files present (use "git add" to track)

### Si crei un nuovo commit che tracci il la ignore list, aggiungendo allo stage i file necessari. Si osservi sempre lo stato del repository dopo l'esecuzione di un comando

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git add .gitignore
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   .gitignore

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git commit -m "Added file ignore list"
[main 880012f] Added file ignore list
 1 file changed, 1 insertion(+)
 create mode 100644 .gitignore
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git status
On branch main
nothing to commit, working tree clean

### Si gestiscano i caratteri di fine linea in modo appropriato, creando un file `.gitattributes`

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ echo "* text=auto eol=lf
dquote> *.[cC][mM][dD] text eol=crlf
dquote> *.[bB][aA][tT] text eol=crlf
dquote> *.[pP][sS]1 text eol=crlf" > .gitattributes
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ cat .gitattributes
* text=auto eol=lf
*.[cC][mM][dD] text eol=crlf
*.[bB][aA][tT] text eol=crlf
*.[pP][sS]1 text eol=crlf
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git add .gitattributes
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git commit -m "Added attributes for carriage return files"
[main 9d93c08] Added attributes for carriage return files
 1 file changed, 4 insertions(+)
 create mode 100644 .gitattributes

### Si osservi la storia del repository usando `git log --all --graph`

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git log --all --graph
* commit 9d93c08a5c2f40a1d4babd23536cbbc1d68293c6 (HEAD -> main)
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:34:19 2024 +0200
|
|     Added attributes for carriage return files
|
* commit 880012fe334e5127d4dc41215e46ce4702821981
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:28:16 2024 +0200
|
|     Added file ignore list
|
* commit 8c860d343a4cdf1061d99efd3642d5dc12232e81
  Author: Davide Mancini <davide.mancini10@studio.unibo.it>
  Date:   Sat Oct 26 14:24:00 2024 +0200

      Added HelloWorld class

### Da questo punto in poi, prima e dopo ogni comando, ci si assicuri di osservare lo stato del repository con `git status`

### Si crei un file Mistake.java, con contenuto arbitrario, lo si aggiunga al tracker, e si faccia un commit

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ echo "x" > Mistake.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        Mistake.java

nothing added to commit but untracked files present (use "git add" to track)
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git add Mistake.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   Mistake.java

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git commit -m "Added Mistake file for testing"
[main 60ee1ca] Added Mistake file for testing
 1 file changed, 1 insertion(+)
 create mode 100644 Mistake.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git status
On branch main
nothing to commit, working tree clean

### Si rinomini `Mistake.java` in `ToDelete.java`, e si faccia un commit che registra la modifica

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ mv Mistake.java ToDelete.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    Mistake.java

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        ToDelete.java

no changes added to commit (use "git add" and/or "git commit -a")
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git add Mistake.java ToDelete.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        renamed:    Mistake.java -> ToDelete.java

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git commit -m "Renamed Mistake.java in ToDelete.java"
[main eebfd0b] Renamed Mistake.java in ToDelete.java
 1 file changed, 0 insertions(+), 0 deletions(-)
 rename Mistake.java => ToDelete.java (100%)
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git status
On branch main
nothing to commit, working tree clean

### Si elimini `ToDelete.java` e si registri la modifica in un commit

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ rm ToDelete.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    ToDelete.java

no changes added to commit (use "git add" and/or "git commit -a")
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git add ToDelete.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        deleted:    ToDelete.java

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git commit -m "Removed file created by mistake"                                                                                                                                                        130 ↵
[main a5000c6] Removed file created by mistake
 1 file changed, 1 deletion(-)
 delete mode 100644 ToDelete.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git status
On branch main
nothing to commit, working tree clean

### Si osservi la storia del repository e si identifichi il commit dove è stato creato `Mistake.java`. Per una visione compatta, si usi l'opzione `--oneline`

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git log --all --oneline
a5000c6 (HEAD -> main) Removed file created by mistake
eebfd0b Renamed Mistake.java in ToDelete.java
60ee1ca Added Mistake file for testing
9d93c08 Added attributes for carriage return files
880012f Added file ignore list
8c860d3 Added HelloWorld class

### Si ripristini Mistake.java dal commit identificato al passo precedente

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git checkout HEAD~2 -- Mistake.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   Mistake.java

### Si rimuova il file ripristinato e si ripulisca lo stage

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ rm Mistake.java
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git status
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   Mistake.java

Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    Mistake.java

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main●›
╰─$ git rm Mistake.java
rm 'Mistake.java'
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git status
On branch main
nothing to commit, working tree clean

### Si torni al commit precedente a quello in cui `Mistake.java` è stato creato. Si utilizzi la storia del repository se utile.

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git checkout main~2
Note: switching to 'main~2'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by switching back to a branch.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -c with the switch command. Example:

  git switch -c <new-branch-name>

Or undo this operation with:

  git switch -

Turn off this advice by setting config variable advice.detachedHead to false

HEAD is now at 60ee1ca Added Mistake file for testing
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹60ee1ca›
╰─$ git status
HEAD detached at 60ee1ca
nothing to commit, working tree clean

### Si crei un nuovo branch di nome `experiment` e si agganci la `HEAD` al nuovo branch

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹9d93c08›
╰─$ git branch experiment
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹9d93c08›
╰─$ git checkout experiment
Switched to branch 'experiment'
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment›
╰─$ git log --all --graph
* commit a5000c60e0a95d859dcd9325c4ac05e30909e83a (main)
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:51:18 2024 +0200
|
|     Removed file created by mistake
|
* commit eebfd0b41fa8964fe829b2e9bd02468d0eeffa2a
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:49:59 2024 +0200
|
|     Renamed Mistake.java in ToDelete.java
|
* commit 60ee1ca94a410597109f87757bdee52a4704d5a2
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:37:06 2024 +0200
|
|     Added Mistake file for testing
|
* commit 9d93c08a5c2f40a1d4babd23536cbbc1d68293c6 (HEAD -> experiment)
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:34:19 2024 +0200
|
|     Added attributes for carriage return files
|
* commit 880012fe334e5127d4dc41215e46ce4702821981
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:28:16 2024 +0200
|
|     Added file ignore list
|
* commit 8c860d343a4cdf1061d99efd3642d5dc12232e81
  Author: Davide Mancini <davide.mancini10@studio.unibo.it>
  Date:   Sat Oct 26 14:24:00 2024 +0200

      Added HelloWorld class

### Si crei un file README.md con contenuto a piacere, e si faccia un commit che lo includa

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment›
╰─$ git status
On branch experiment
nothing to commit, working tree clean
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment›
╰─$ echo "# Exercise 54 OOP" > README.md
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment●›
╰─$ git status
On branch experiment
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md

nothing added to commit but untracked files present (use "git add" to track)
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment●›
╰─$ git add README.md
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment●›
╰─$ git status
On branch experiment
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   README.md

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment●›
╰─$ git commit -m "Added README file to experimental branch"
[experiment 83a6ad5] Added README file to experimental branch
 1 file changed, 1 insertion(+)
 create mode 100644 README.md
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment›
╰─$ git status
On branch experiment
nothing to commit, working tree clean
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment›
╰─$ git log --all --graph
* commit 83a6ad514a2842a562d03d5e132e3b8e600b62ca (HEAD -> experiment)
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 15:42:08 2024 +0200
|
|     Added README file to experimental branch
|
| * commit a5000c60e0a95d859dcd9325c4ac05e30909e83a (main)
| | Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| | Date:   Sat Oct 26 14:51:18 2024 +0200
| |
| |     Removed file created by mistake
| |
| * commit eebfd0b41fa8964fe829b2e9bd02468d0eeffa2a
| | Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| | Date:   Sat Oct 26 14:49:59 2024 +0200
| |
| |     Renamed Mistake.java in ToDelete.java
| |
| * commit 60ee1ca94a410597109f87757bdee52a4704d5a2
|/  Author: Davide Mancini <davide.mancini10@studio.unibo.it>
|   Date:   Sat Oct 26 14:37:06 2024 +0200
|
|       Added Mistake file for testing
|
* commit 9d93c08a5c2f40a1d4babd23536cbbc1d68293c6
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:34:19 2024 +0200
|
|     Added attributes for carriage return files
|
* commit 880012fe334e5127d4dc41215e46ce4702821981
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:28:16 2024 +0200
|
|     Added file ignore list
|
* commit 8c860d343a4cdf1061d99efd3642d5dc12232e81
  Author: Davide Mancini <davide.mancini10@studio.unibo.it>
  Date:   Sat Oct 26 14:24:00 2024 +0200

      Added HelloWorld class

### Si torni sul branch master e si elenchino i branch disponibili

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹experiment›
╰─$ git checkout main
Switched to branch 'main'
╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git branch -v
  experiment 83a6ad5 Added README file to experimental branch
* main       a5000c6 Removed file created by mistake

### Si unisca il branch experiment al branch master (si faccia un merge in cui experiment viene messo dentro master, e non viceversa)

╭─davide@Davide ~/Projects/unibo_projects/OOP/oop-lab05/54-branching/ex54 ‹main›
╰─$ git merge experiment
Merge made by the 'ort' strategy.
 README.md | 1 +
 1 file changed, 1 insertion(+)
 create mode 100644 README.md

### Si osservi la storia del repository

*   commit 394f9c11b1c1953625846bd0632bbabd4672950f (HEAD -> main)
|\  Merge: a5000c6 83a6ad5
| | Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| | Date:   Sat Oct 26 16:04:04 2024 +0200
| |
| |     Merge branch 'experiment'
| |
| * commit 83a6ad514a2842a562d03d5e132e3b8e600b62ca (experiment)
| | Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| | Date:   Sat Oct 26 15:42:08 2024 +0200
| |
| |     Added README file to experimental branch
| |
* | commit a5000c60e0a95d859dcd9325c4ac05e30909e83a
| | Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| | Date:   Sat Oct 26 14:51:18 2024 +0200
| |
| |     Removed file created by mistake
| |
* | commit eebfd0b41fa8964fe829b2e9bd02468d0eeffa2a
| | Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| | Date:   Sat Oct 26 14:49:59 2024 +0200
| |
| |     Renamed Mistake.java in ToDelete.java
| |
* | commit 60ee1ca94a410597109f87757bdee52a4704d5a2
|/  Author: Davide Mancini <davide.mancini10@studio.unibo.it>
|   Date:   Sat Oct 26 14:37:06 2024 +0200
|
|       Added Mistake file for testing
|
* commit 9d93c08a5c2f40a1d4babd23536cbbc1d68293c6
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:34:19 2024 +0200
|
|     Added attributes for carriage return files
|
* commit 880012fe334e5127d4dc41215e46ce4702821981
| Author: Davide Mancini <davide.mancini10@studio.unibo.it>
| Date:   Sat Oct 26 14:28:16 2024 +0200
|
|     Added file ignore list
|
* commit 8c860d343a4cdf1061d99efd3642d5dc12232e81
  Author: Davide Mancini <davide.mancini10@studio.unibo.it>
  Date:   Sat Oct 26 14:24:00 2024 +0200

      Added HelloWorld class
