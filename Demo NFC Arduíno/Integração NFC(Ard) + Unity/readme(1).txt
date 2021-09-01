O codigo ScriptPlayer.cs desta pasta é um codigo em que o personagem atira se a a tag NFC foi lida.
Esse ScriptPlayer veio de um codigo de um personaagem que eu fiz pra um joguinho
O que interessa é o seguinte:
Bota dentro da classe:
SerialPort porta = new SerialPort("COM3", 9600);

Em Start:
void Start () {
		porta.Open();
        porta.ReadTimeout = 50;
	}
	
Em update:
Se a porta tiver aberta, lê o que é enviado pelo arduino (o id da TAG NFC)
if(porta.IsOpen)
        {
            try
            {
                str = porta.ReadLine();
                Debug.Log(str);
				print(str);
            }
            catch(System.Exception)
            {

            }
        }	