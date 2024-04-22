from User import User

def menu(opc):
    if opc==1:
        print("registro banco LOS NACOS")
        name=input("Nombre: ")
        age=input("Edad: ")
        password=input("Contrasenia: ")
        valPass=input("Validar contrasenia")
        gender=input("Genero: ")
        client=User()
        client.register(name,age,password,valPass,gender)
    elif opc==2:
        print("Login")
        noCard=input("Ingrese numero de tarjeta: ")
        password=input("Ingrese contrasenia: ")
        client=User()
        client.Login(noCard,password)
        print("\n\n\n\n\n\n\n\n")
        print("1.-Depositar")
        print("2.-Retirar")
        print("3.-Transferir")
        print("4.-Mostrar informacion cuenta")
        opc2=int(input("Elija una opcion: "))
        print("\n\n\n\n\n\n\n\n")
        if opc2 == 1:
            amount=float(input("Ingrese cantidad a depositar: "))
            client.account.DepositCash(amount)
        elif opc2 ==2:
            amount=float(input("Ingrese cantidad a retirar: "))
            client.account.WithdrawCash(amount)
        elif opc2 ==3:
            trans=2
        elif opc2 ==4:
            client.account.CheckBalance()


        






print("1.-Registrarse")
print("2.-login")
opc=int(input("Elija una opcion: "))
menu(opc)

