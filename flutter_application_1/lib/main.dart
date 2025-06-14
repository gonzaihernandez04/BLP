import 'package:flutter/material.dart';
import 'newacount_screen.dart';
void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: LoginScreen(),
    );
  }
}

class LoginScreen extends StatefulWidget {
  @override
  _LoginScreenState createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  final TextEditingController _emailController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();

  // Simula el proceso de autenticación
  Future<void> _login() async {
    String email = _emailController.text;
    String password = _passwordController.text;

    // Aquí puedes reemplazar este proceso con tus propias validaciones o backend
    if (email == "usuario@ejemplo.com" && password == "123456") {
      // Si el login es exitoso
      print("Login exitoso");
      // Aquí puedes redirigir al usuario a otra pantalla, por ejemplo:
      // Navigator.pushReplacement(context, MaterialPageRoute(builder: (context) => HomeScreen()));
    } else {
      // Si el login falla
      showDialog(
        context: context,
        builder: (context) => AlertDialog(
          title: Text("Error de login"),
          content: Text("Correo o contraseña incorrectos"),
          actions: [
            TextButton(
              onPressed: () {
                Navigator.of(context).pop();
              },
              child: Text('Cerrar'),
            ),
          ],
        ),
      );
    }
  }

  // En caso de no tener sesion 
  Future<void> _newLogin() async {
     Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => SignUpScreen()),
                );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Login Calistenia App"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: [
            TextField(
              controller: _emailController,
              decoration: InputDecoration(
                labelText: 'Correo electrónico',
                border: OutlineInputBorder(),
              ),
            ),
            SizedBox(height: 16),
            TextField(
              controller: _passwordController,
              obscureText: true,
              decoration: InputDecoration(
                labelText: 'Contraseña',
                border: OutlineInputBorder(),
              ),
            ),
            SizedBox(height: 16),
            ElevatedButton(
              onPressed: _login,
              child: Text('Iniciar sesión'),
            ),SizedBox(height: 16),
            ElevatedButton(
              onPressed: _newLogin,
              child: Text('¿No tienes cuenta? Crea una ahora!'),
            ),
          ],
        ),
      ),
    );
  }
}