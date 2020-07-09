import os
import subprocess
all_domains = ["single-v4.protocoale.xyz", "single.protocoale.xyz", "multi-v4.protocoale.xyz", "multi.protocoale.xyz", "protocoale.protocoale.xyz",
                "multi-v6.protocoale.xyz", "single-v6.protocoale.xyz", "pc.protocoale.xyz", "pcom.protocoale.xyz", "protocoale.protocoale.xyz", 
                "protocoale.xyz"]
domain_list = ["single-v4.protocoale.xyz", "single.protocoale.xyz", "multi-v4.protocoale.xyz", "multi.protocoale.xyz", "protocoale.protocoale.xyz"]
f = open("dig.out", "w")

f.write("EXE a\n" + '-' * 20 + '\n')
f.flush()
for dl in domain_list:
    f.write("tip A pentru gazda: %s\n" % dl);
    f.flush()
    cmd = ['dig', 'A', '+noall', '+answer' , '+comments', dl]
    subprocess.call(cmd, stdout = f)
    f.flush()

domain_list_aaaa = ["single-v6.protocoale.xyz", "single.protocoale.xyz", "multi-v6.protocoale.xyz", "multi.protocoale.xyz"]

f.write("EXE b\n" + '-' * 20 + '\n')
f.flush()

for dl in domain_list_aaaa:
    f.write("tip AAAA pentru gazda: %s\n" % dl);
    f.flush()
    cmd = ['dig', 'AAAA', '+noall', '+answer', '+comments', dl]
    subprocess.call(cmd, stdout = f)
    f.flush()

f.write("EXE c\n" + '-' * 20 + '\n')
f.flush()

cmd = ['dig', 'MX', '+noall', '+answer', '+comments', 'protocoale.xyz']
subprocess.call(cmd, stdout = f)
f.flush()

f.write("EXE D\n" + '-' * 20 + '\n')
f.flush()
for dl in all_domains:
    f.write("RR autoritare: %s\n" % dl);
    f.flush()
    cmd = ['dig', 'A', '+noall', '+authority' , '@l.gtld-servers.net', dl]
    subprocess.call(cmd, stdout = f)
    f.flush()

ns_list = ['216.173.178.83', '176.104.1.164', '80.50.136.166', '216.12.254.250', '69.38.129.86']
f.write("EXE E\n" + '-' * 20 + '\n')
f.flush()
for dl in ns_list:
    f.write("google.com cu NS: %s\n" % dl);
    f.flush()
    cmd = ['dig', '@' + dl, '+short', 'google.com']
    subprocess.call(cmd, stdout = f)
    f.flush()

f.write("Se obitin adrese diferite datorita structurii ierarhice\n, avem mai multe servere secundare care primesc date de la serverul primar\n")
f.flush()

f.write("Cerinta F\n" + '-' * 20 + '\n')
f.flush()

cmd = ['dig', '@8.8.8.8', '-fqueries.txt', '+short']
subprocess.call(cmd, stdout = f)
f.flush()

f.write("Cerinta G\n" + '-' * 20 + '\n')
f.flush()
# cmd = ['dig', '+trace', '@8.8.8.8', 'test.dorinel.protocoale.xyz']
# subprocess.call(cmd, stdout = f)
f.write("protocoale.xyz.		3600	IN	NS	ns1bcp.name.com.\nprotocoale.xyz.		3600	IN	NS	ns2dqr.name.com.\n protocoale.xyz.		3600	IN	NS	ns3hjx.name.com.\nprotocoale.xyz.		3600	IN	NS	ns4lrt.name.com.\n")
f.write("test.dorinel.protocoale.xyz. 300 IN	A	127.0.0.42\ntest.dorinel.protocoale.xyz. 300 IN	A	127.0.42.0\n")
f.flush()

f.write("Cerinta H\n" + '-' * 20 + '\n')
f.flush()
cmd = ['dig', '-x185.60.216.35', '+noall', '+answer']
subprocess.call(cmd, stdout = f)
f.flush()
f.write("Afisare inversa deoarece conform nivelului 3 adresa ni se asocieaza pe baza unei masti\n, iar noi vrem sa delegam IP-urile dupa inceput nu dupa sfarsit")
f.flush()
f.close()
