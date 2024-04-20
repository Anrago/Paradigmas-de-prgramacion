import Account
from Person import Person
from random import randint

class User(Person):
    def __init__(self):
        super().__init__('','','')
        self.password=''
        self.noCard=0
        self.noClient=0
        self.InterBaKey=''
    def register(self): 
        print("Bienvenido a sistema de registro del Banco LOS NACOS.")
        print("Este registro no le llevara mas de 5 minutos.")
        self.name=input("Ingrese su nombre: ")
        self.age=input("Ingrese su edad: ")
        if int(self.age)<18:
            print("Lo sentimos, para crear una cuenta se debe de contar con una edad minima de 18 años:")
            return
        self.gender=input("Ingrese su genero: ")
        self.password=input("Escriba su contraseña: ")
        while(True):
            Ptemp=input("Confirmar contraseña: ")
            if self.password!=Ptemp:
                print("Las contraseñas no coincide. Favor de intentarlo nuevamente")
            else:
                break
        print("La cuenta ha sido creada con exito")
        print("Bienvenido al la familia de LOS NACOS.")
        self.noCard=randint(1000000000000000,9999999999999999)
        self.InterBaKey='542965'+str(randint(10000000000,99999999999))+str(randint(0,5))
        self.noClient=randint(10000,99999)
        print("Su numero de cliente es: ",self.noClient)
        print("Su No. de tarjeta es: ",self.noCard) 
        print("Su clave interbacaria es: ",self.InterBaKey)
        print("Con cualquiera de estos dos numero podar iniciar sesion o realizar transferencias")
        fa=open("Bank/Cuentas.txt","a")
        fa.write(self.noClient + ' ' + self.name + ' ' + self.password + ' ' +  '\n')
        fa.close()
u=User()
u.register()
        
        


    








