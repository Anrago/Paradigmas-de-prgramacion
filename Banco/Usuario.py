
class Usuario:

    def __init__(self,Nombre,Contrasenia,No_cuenta):
        self.Nombre=Nombre
        self.Contrasenia=Contrasenia
        self.No_cuenta=No_cuenta
    def MostrarInfo(self):
        print(f"HOLA {self.Nombre}")
