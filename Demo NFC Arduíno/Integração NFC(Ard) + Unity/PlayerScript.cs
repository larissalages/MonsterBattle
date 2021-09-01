using UnityEngine;
using System.Collections;
using System.IO.Ports;


public class PlayerScript : MonoBehaviour {

	SerialPort porta = new SerialPort("COM3", 9600);
    /// <summary>
    /// 1 - The speed of the ship
    /// </summary>
    public Vector2 speed = new Vector2(50, 50);

    // 2 - Store the movement
    private Vector2 movement;

    // Use this for initialization
    void Start () {
		porta.Open();
        porta.ReadTimeout = 50;
	}
	
	// Update is called once per frame
	void Update ()
    {
		System.String str = "";
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
        // 3 - Retrieve axis information
        float inputX = Input.GetAxis("Horizontal");
        float inputY = Input.GetAxis("Vertical");

        // 4 - Movement per direction
          movement = new Vector2(
          speed.x * inputX,
          speed.y * inputY);

        // 5 - Shooting
        bool shoot = Input.GetButton("Fire1");
        shoot |= Input.GetButton("Fire2");
        // Careful: For Mac users, ctrl + arrow is a bad idea
		
		
			
        if (str.Equals("F1 2A F2 52"))
        {
            WeaponScript weapon = GetComponent<WeaponScript>();
            if (weapon != null)
            {
                // false because the player is not an enemy
				print("ATACOUUU CRLHH");
                weapon.Attack(false);
            }
        }
    }
    void FixedUpdate()
    {
        // 5 - Move the game object
        //rigidbody2D.velocity = movement;
        GetComponent<Rigidbody2D>().velocity = movement;
    }
}
