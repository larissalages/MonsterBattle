using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class ShowImage : MonoBehaviour {

    public Sprite[] monster_sprites;
    SpriteRenderer sr;
    SerialPort porta = new SerialPort("COM3", 9600);

    // Use this for initialization
    void Start ()
    {
        sr = GetComponent<SpriteRenderer>();
        sr.sprite = monster_sprites[5];
        porta.Open();
        porta.ReadTimeout = 50;
    }
	
	// Update is called once per frame
	void Update ()
    {
        System.String str = "";
        if (porta.IsOpen)
        {
            try
            {
                str = porta.ReadLine();
                //Debug.Log(str);
                //print(str);
            }
            catch (System.Exception)
            {

            }
        }

        if (str == "04 1E C4 22 0A 40 80")
            sr.sprite = monster_sprites[0];
        else if (str == "04 37 C3 22 0A 40 80")
            sr.sprite = monster_sprites[1];
        else if (str == "04 22 C3 22 0A 40 80")
            sr.sprite = monster_sprites[2];
        else if (str == "04 1D C4 22 0A 40 80")
            sr.sprite = monster_sprites[3];
        else if (str == "04 32 C4 22 0A 40 80")
            sr.sprite = monster_sprites[4];
        //else
            //sr.sprite = monster_sprites[8];

    }
}