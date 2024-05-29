                                BORN2BEROOT


What is a Virtual machine


A "virtual machine" was originally defined by Popek and Goldberg as "an efficient, isolated duplicate of a real computer machine."
Current use includes virtual machines that have no direct correspondence to any real hardware.
The physical, "real-world" hardware running the VM is generally referred to as the 'host', and the virtual machine emulated on that machine is generally referred to as the 'guest'.
A host can emulate several guests, each of which can emulate different operating systems and hardware platforms.
The desire to run multiple operating systems was the initial motive for virtual machines, so as to allow time-sharing among several single-tasking operating systems.

There are several scenarios that make virtualization attractive:

    Operating system support. With a virtualizer such as VirtualBox,
    one can run software written for one operating system on another (say, Windows software on Linux) without having to reboot.

    Infrastructure consolidation. Since the full performance of today's computers is rarely needed full-time,
    instead of running many such physical computers, one can "pack" many virtual machines onto a few powerful hosts and balance the loads between them.
    This can save a lot of hardware costs: e.g. by consolidating many servers into a few.
    VirtualBox is unique on the virtualization market in that it also allows for consolidating clients onto just a few RDP(Remote Desktop Protocole) servers,
    with full client USB support, while "thin clients" only need to display RDP data.

    Testing and disaster recovery. Especially with the use of snapshots?,
    one can mess with a computing environment by running it as a virtual machine.
    If something goes wrong, one can easily switch back to a previous snapshot and avoid the need of frequent backups and restores.


What is virtual disk signature?

A disk signature is a unique, identifying number for a hard disk drive or other data storage device stored as part of the master boot record.
An operating system uses it to differentiate among storage devices on your computer.
//A disk signature consists of eight alphanumeric digits from 0 to 9 and A to F.


    APT VS Aptitude

Aptitude and apt-get are two of the popular tools which handle package management.
Both are capable of handling all kinds of activities on packages including installation, removal, search etc.
But still there are differences between both the tools which make users prefer one over the other.

Apt: Is whole command line with no GUI.
Whenever invoked from command line along with specifying the name of package to be installed,
it finds that package in configured list of sources specified in ‘/etc/apt/sources.list’ along with the list of dependencies for that package and
sorts them and automatically installs them along with the current package thus letting user not to worry of installing dependencies.
Apt-get being a lower level package manager is restricted only to command line,
while Aptitude being a higher-level tool has a default text-only interactive interface along with option of command-line operation by entering required commands.

Aptitude: Its user interface is based on ncurses library which adds various elements to it commonly seen in GUI’s.
One of its highlight is that it can emulate most of apt-get’s command line arguments.
In all, Aptitude is a higher-level package managers that abstracts low level details,
and can operate in both text-based interactive UI mode and even in command line non-interactive mode.
While apt-get lacks UI, Aptitude has a text-only and interactive UI.
Aptitude has a better package management than apt-get.
Aptitude is vaster in functionality than apt-get and integrates functionalities of apt-get and its other variants including apt-mark and apt-cache.


Apart from main difference being that Aptitude is a high-level package manager while APT is lower-level package manager which can be used by other higher-level package managers
So, for most of the cases, syntax of Aptitude is kept almost same as that of apt-get, to make users of apt-get have less pain in migrating to Aptitude,
but in addition to this, many powerful features are integrated in Aptitude that make it the one to be chosen.

    SELINUX VS APPARMOR

https://francoandroid.com/selinux-vs-apparmor-quelles-sont-les-differences-et-lequel-utiliser/

SELinux (abréviation de Security Enhanced Linux) est un module de sécurité du noyau Linux utilisé pour accroître la sécurité des distributions Linux en renforçant l’accès aux fichiers et aux processus.
Un autre module de sécurité du noyau Linux similaire utilisé à cette fin est AppArmor.
Ces deux modules suscitent beaucoup d’intérêt en raison de leurs rôles qui se chevauchent dans le contrôle d’accès pour les systèmes d’exploitation Linux.

//Cet article couvre les différences entre SELinux et AppArmor,
//permettant aux utilisateurs de déterminer lequel de ces modules répond le mieux à leurs besoins grâce à une comparaison des fonctionnalités et de la facilité d’utilisation.


AppArmor est soutenu en développement par Canonical, la société mère qui développe la distribution Ubuntu de Linux.
AppArmor se veut plus simple et plus facile à utiliser que SELinux et ses profils sont créés dans le répertoire « /etc/apparmor.d/ ».

    Conclusion

AppArmor fonctionne avec des chemins de fichiers dans le système de fichiers au lieu de travailler avec des chaînes pour chaque fichier comme le fait SELinux.
L’un des avantages d’AppArmor est que les opérations de lecture, d’écriture,
de verrouillage et autres opérations sur les fichiers sont plus faciles à configurer que dans SELinux.
D’autre part, alors que SELinux fournit plus de fonctionnalités pour le contrôle d’accès aux fichiers,
les fonctionnalités sont implémentées à un niveau beaucoup plus bas dans le système.

Par conséquent, les utilisateurs doivent apprendre à utiliser mknod, les sockets réseau et d’autres opérations système pour travailler avec SELinux.
Pour tous ceux qui ne sont pas administrateur système, il est beaucoup plus facile d’ apprendre à utiliser AppArmor .

AppArmor fournit également un mode d’apprentissage utilisé pour consigner les violations du contrôle d’accès.
Ce mode ne restreint ni n’empêche l’accès en cas de violation,
mais collecte des données au fil du temps pour permettre la création d’un profil AppArmor distinct basé sur le comportement des programmes pour chaque infraction d’accès enregistrée.
Il n’y a pas de mode similaire disponible dans SELinux.

These security systems provide tools to isolate applications from each other... and in turn isolate an attacker from the rest of the system when an application is compromised.
SELinux rule sets are incredibly complex but with this complexity you have more control over how processes are isolated.
Generating these policies can be automated.
A strike against this security system is that its very difficult to independently verify.
AppArmor (and SMACK) is very straight forward.
The profiles can be hand written by humans, or generated using aa-logprof.
AppArmor uses path based control, making the system more transparent so it can be independently verified.


List of usefull command

    su autre_login : se connecter en tant qu’un autre utilisateur. On nous demandera alors le mot de passe de l’autre utilisateur. Lancer su (switch user) sans préciser d’utilisateur nous permettra de se connecter en tant que l’utilisateur par defaut, root. On peut exit pour retourner à la session précédente.

    exit ou logout : termine la session en cours et nous renvoie à l’écran de connexion.


    apt uptade : met a jour la liste des paquets disponibles

    apt upgrade : met a jour les paquets

                MAN SYSTEMCTL

    systemctl status PATTERN, PID... : Show terse runtime status information about one or more units, followed by most recent log data from the journal.

    systemctl start PATTERN... : Activate onr or more units specfied o the command line.

    systemctl stop PATTERN... : Deactivate one or ;ore untis specified on the command line.

    systemctl enable UNIT...,PATH... : Enable onr or ore untis or unit instances. This will create a set of symlinks, as encoded in the [Install] sections of the indicated unit files.
                                       After the symlinks have been created, the system manager configuration is reloaded(in way equivalent to deamon-reload)

    systemctl reload PATTERN... : Asks all units lited on the command line to reload theur configuration.
                                  If you want systemd to reload the configuration file of a unit, use the daemon-reload command.
                                  This command should not be confused with the daemon-reload command.

    systemctl restart PATTERN... : Stop and then start one or more untis specified on the command line. If the units are not running yet, they will be started.

    systemctl reboot : redémarre le système (permissions root requises)

    systemctl poweroff : éteint le système (permissions root requises)


                MAN CHAGE

    chage -M (--maxdays) <username> : Fixer le nombre maximum de jours pendant lesquels un mot de passe est valable.

    chage -m (--mindays) <username> : Définit le nombre minimum de jours entre chaque changement de mot de passe.

    chage -w (--warndays) <username> : Fixer le nombre de jours d'avertissement avant que le changement de mot de passe ne soit obligatoire.

    chage -l <username> : affiches les info du user

                MAN PASSWD

    `sudo` passwd <username> : La  commande  passwd  modifie  les  mots  de  passe   des  comptes  des utilisateurs.

    passwd -S (--status) : Affiche l'etat d'un compte. 

    passwd -d (--delete) : Supprime le mot de passe (le rend vide) d'un utilisateur. C'est une facon rapide de suprimer l'autehntification par mot de passe pour un compte.
                           Le compte concerne ne possede plus de mot de passe.


                MAN HOSTNAMECTL

    sudo hostnamectl set-hostname <new_hostname> : Change le hostname de la machine virtuelle
                                                   On peut egalement modifier le hostname en editant le fichier "/etc/hostname".
                                                   Le changement de nom prendras effet au redemarrage de la machine.

    hostnamectl status : Show system hostname and related information. If no command is specified, this is the implied default.

                MAN USERMOD

    usermod -aG <group_name> <username> :
            -a --append > add the user to the supplementary group(s). Use only with -G option
            -G --groups > A list of supplementary groups which the user is also a member of.
                          Each group is separated from the next by a comma, with no intervening whitespace.
                          The groups are subject to the same restrictions as the group given with the -g option.

                MAN GETENT

    The getent command displays entries from databases supported by
       the Name Service Switch libraries, which are configured in
       /etc/nsswitch.conf.  If one or more key arguments are provided,
       then only the entries that match the supplied keys will be
       displayed.  Otherwise, if no key is provided, all entries will be
       displayed (unless the database does not support enumeration).

    getent group <group_name>


                MAN VISUDO

    sudo visudo : The sudoers policy module determines a user's sudo privileges.
        It is the default sudo policy plugin.
        The policy is driven by the /etc/sudoers file or, optionally in LDAP.
        The policy format is described in detail in the SUDOERS FILE FORMAT section.
        For information on storing sudoers policy information in LDAP, please see sudoers.ldap(5)


        List des paquets installer

            apt install sudo
            apt install ufw
            apt install libpam-pwquality
            apt install openssh-server

        Modification des utilisateurs

            adduser : crée un nouvel utilisateur.

            usermod : modifie les paramètres de l’utilisateur : -l pour le login, -c pour le nom entier, -g pour les groupes par numéro d’identification de groupe.

            deluser -r : supprime l’utilisateur et tout ses fichiers.

            id -u : affiche le numéro d’identification de l’utilisateur.

            users : montre une liste de tous les utilisateurs connectés à l’instant.

        Manipulation des groupes

            groupadd : crée un nouveau groupe.
            gpasswd -a : ajoute un utilisateur à un groupe.
            gpasswd -d : enlève un utilisateur d’un groupe.
            groupdel : supprime un groupe.
            groups : affiche les groupes dans lesquels se trouve un utilisateur.
            id -g : montre le numéro d’identification du groupe principal d’un utilisateur.
            getent group : affiche la liste des utilisateurs dans un groupe.

        FICHIERS

            /etc/group
            Informations sur les groupes.
            /etc/gshadow
            Informations sécurisées sur les groupes.
            /etc/login.defs
            Configuration de la suite des mots de passe cachés « shadow password ».
            /etc/passwd
            Informations sur les comptes des utilisateurs.

        SSH & configuring SSH service

            sudo apt install openssh-server

            sudo systemctl status ssh

            sudo nano /etc/ssh/sshd_config: CHANGE #Port 22 > Port 4242

            sudo systemctl restart ssh

                Connecting SSH-server

                1. Go to VirtualBox-> Choose the VM->Select Settings

                2. Choose “Network”-> “Adapter 1"->”Advanced”->”Port Forwarding”

                3. Set the protocole to TCP, Host port to 4242, Guest port 4242

            sudo systemctl restart ssh

            sudo systemctl status sshd

                Connecting with SSH

                    ssh username@127.0.0.1 -p 4242
                    ssh username@localhost -p 4242

                    why ssh username@(ip a) -p 4242 doesnt work ?

                    exit

        UFW & configuring UFW (Uncomplicated Firewall)

            sudo apt install ufw

            sudo ufw enable
            
            sudo ufw allow 4242

            sudo ufw status numbered ( display the list of rules with number)

                TEST FOR UFW DENY/ALLOW outgoing

            $ sudo ufw status verbose
            $ sudo ufw default deny outgoing
            $ sudo apt update > FAIL due to deny outgoing
            $ sudo ufw default allow outgoing
            $ sudo apt update > SUCCESS due to allow outgoing
            $ sudo ufw deny 4242
                SSH > FAIL
            $ sudo ufw allow 4242
                SSH > SUCCESS

        Set password policy

            sudo nano /etc/login.defs

            /etc/login.defs : The /etc/login.defs file defines the site-specific configuration
                              for the shadow password suite. This file is required. Absence of
                              this file will not prevent system operation, but will probably
                              result in undesirable operation.

                PASS_MAX_DAYS 30
                PASS_MIN_DAYS 2
                PASS_WARN_AGE 7

            sudo apt install libpam-pwquality

                sudo nano /etc/security/pwquality.conf

                # Number of characters in the new password that must not be present in the 
                # old password.
                difok = 7
                # The minimum acceptable size for the new password (plus one if 
                # credits are not disabled which is the default)
                minlen = 10
                # The maximum credit for having digits in the new password. If less than 0 
                # it is the minimun number of digits in the new password.
                dcredit = -1
                # The maximum credit for having uppercase characters in the new password. 
                # If less than 0 it is the minimun number of uppercase characters in the new 
                # password.
                ucredit = -1
                # ...
                # The maximum number of allowed consecutive same characters in the new password.
                # The check is disabled if the value is 0.
                maxrepeat = 3
                # ...
                # Whether to check it it contains the user name in some form.
                # The check is disabled if the value is 0.
                usercheck = 1
                # ...
                # Prompt user at most N times before returning with error. The default is 1.
                retry = 3
                # Enforces pwquality checks on the root user password.
                # Enabled if the option is present.
                The module will return error on ailed check even if the user changing the password is root.
                This option is off by default which means that just the message about the failed check is printed but root can change the password anyway.
                Note that root is not asked for an old password so the checks that compare the old and new password are not performed.
                enforce_for_root
                # ...

        SUDO &  Configuration sudo

            sudo apt install sudo

            mkdir /var/log/sudo

            sudo visudo

                Defaults     passwd_tries=3
                Defaults     insults
                Defaults     logfile="/var/log/sudo/sudo.log"
                Defaults     log_input
                Defaults     log_output
                Defaults     requiretty
                Defaults      path??   /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin

            User Privilege Lines

                The fourth line, which dictates the root user’s sudo privileges, is different from the preceding lines. Let’s take a look at what the different fields mean:

                root ALL=(ALL:ALL) ALL The first field indicates the username that the rule will apply to (root).
                *  
                root ALL=(ALL:ALL) ALL The first “ALL” indicates that this rule applies to all hosts.
                    *
                root ALL=(ALL:ALL) ALL This “ALL” indicates that the root user can run commands as all users.
                        *
                root ALL=(ALL:ALL) ALL This “ALL” indicates that the root user can run commands as all groups.
                            *
                root ALL=(ALL:ALL) ALL The last “ALL” indicates these rules apply to all commands.
                                    *
                This means that our root user can run any command using sudo, as long as they provide their password.


        MONTORING.SH

            La commande wall est celle qui permet d’envoyer un message à tous les utilisateurs à la fois, qui s’affiche dans tous les terminaux.
            Elle peut recevoir soit du texte, soit le contenu d’un fichier.
            Par défaut, elle préfixe l’annonce d’un bandeau.
            Ce bandeau est optionnel dans ce projet.

            wall "message"

                uname -srvmo

                grep 'physical id' /proc/cpuinfo | uniq | wc -l

                grep processor /proc/cpuinfo | uniq | wc -l

                free --mega | grep Mem | awk '{printf(" %i/%iMB (%.2f%%)\n", $3, $2, $3/$2*100}'

                df --total --human-readable | grep "total" | awk '{printf(" %s\%s (%.1f%%)\n", $3, $2, $3/2*100)}'

                top -bn1 | grep "%Cpu" | awk '{printf("CPU load: %.1f%%\n", (100.0-$8)%100)}'

                who --boot | awk '{printf("Last boot: %s %s", $3, $4)}'

                if [ $(lsblk | grep "lvm" | wc -l) -eq 0 ]; then echo "no"; else echo "yes"; fi

                ss -s | grep "TCP:" | tr ',' ' ' | awk '{printf(" %s ESTABLISHED\n", $4)}'

                who --count | grep "users" | tr '=' ' ' | awk '{printf(" %s\n", $3)}'

                `hostname -I` (`ip link | grep "ether" | awk '{print($2)}'

                `grep -a COMMAND /var/log/sudo/sudo.log | wc -l`

        CRON

            Cron (ou crontab, chrono table, qui signifie « table de planification ») est un programme qui permet d’exécuter des scripts,
            des commandes ou des logiciels automatiquement, à une date et heure ou un intervalle spécifié. Il est installé par défaut dans Debian (on peut vérifier avec la commande apt list cron).
            Il faut d’abord l’activer pour être certains qu’il se lance au démarrage :

            systemctl enable cron

            sudo crontab -u root -e -> edit the crontab as root "-e edit -u user"

            crontab -l -> list crontab rule for the user 

            # ┌───────────── minute (0 - 59)
            # │ ┌───────────── hour (0 - 23)
            # │ │ ┌───────────── day of the month (1 - 31)
            # │ │ │ ┌───────────── month (1 - 12)
            # │ │ │ │ ┌───────────── day of the week (0 - 6) (Sunday to Saturday;
            # │ │ │ │ │                                   7 is also Sunday on some systems)
            # │ │ │ │ │
            # │ │ │ │ │
            # * * * * * <command to execute>


https://www.it-connect.fr/les-droits-sous-linux/

https://debian-handbook.info/browse/fr-FR/stable/sect.apparmor.html

https://www.howtouselinux.com/post/tcp-vs-udp

https://www.howtouselinux.com/post/tcp-socket

https://www.howtouselinux.com/post/tcp-connection

https://www.digitalocean.com/community/tutorials/how-to-edit-the-sudoers-file

https://www.digitalocean.com/community/tutorials/ufw-essentials-common-firewall-rules-and-commands

            SS -TUNLP

    /etc/network/interfaces

    DEFAULT is 

        # The loopback network interface
            auto lo
            iface lo inet loopback

        # The primary network interface
            allow-hotplug enp0s3
            iface enp0s3 inet dhcp

    DHCP to STATIC ip and close the port 68 

        # The loopback network interface
            auto lo
            iface lo inet loopback

            auto enp0s3
            iface enp0s3 inet static > if i want the statis as ipv6 i have to change the inet -> inet6

            address 10.0.2.15 > ip a give the address
            gateway 10.0.2.2 > ip route give the gateway
            netmask 255.255.255.0 > default netmask
            dns-nameservers 8.8.8.8 8.8.4.4 > this is the public google dns


                    RESOLVCONF

        Was use to automated the configuration of the DHCP to STATIC

https://coagul.org/drupal/publication/r%C3%A9solution-noms-resolvconf-sous-linux-debians


NOT USED

    IPTABLES

was used to clear the dhcp port 68, but not working. -> see the SS -TUNLP section

    iptables -A INPUT -p udp --dport 68 -j DROP ??? ussless ??? or not the effect i excepted

    iptables -S | grep 68


    -A, --append chain rule-specification
        Append one or more rules to the end of the selected chain.
        When the source and/or destination names resolve to more than one address,
        a rule will be added for each possible address combination.

    [!] -p, --protocol protocol
        The protocol of the rule or of the packet to check.
        The specified protocol can be one of tcp, udp, udplite, icmp, icmpv6,esp, ah, sctp, mh or the special keyword "all",
        or it can be a numeric value, representing one of these protocols or a different one.
        A protocol name from /etc/protocols is also allowed.
        A "!" argument before the protocol inverts the test.
        The number zero is equivalent to all.
        "all" will match with all protocols and is taken as default when this option is omitted.
        Note that, in ip6tables, IPv6 extension headers except esp are not allowed.
        esp and ipv6-nonext can be used with Kernel version 2.6.11 or later.
        The number zero is equivalent to all,
        which means that you cannot test the protocol field for the value 0 directly.
        To match on a HBH header, even if it were the last, you cannot use -p 0, but always need -m hbh.

    -m, --match match
        Specifies a match to use, that is, an extension module that tests for a specific property.
        The set of matches make up the condition under which a target is invoked.
        Matches are evaluated first to last as specified on the command line and work in short-circuit fashion, i.e.
        if one extension yields false, evaluation will stop.

    -j, --jump target
        This specifies the target of the rule; i.e., what to do if the packet matches it.
        The target can be a user-defined chain (other than the one this rule is in),
        one of the special builtin targets which decide the fate of the packet immediately,
        or an extension (see EXTENSIONS below).
        If this option is omitted in a rule (and -g is not used),
        then matching the rule will have no effect on the packet's fate,
        but the counters on the rule will be incremented.
