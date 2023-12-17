using UnityEngine;

namespace Invector.vCharacterController
{
    public class vThirdPersonInput : MonoBehaviour
    {
        #region Variables       

        [Header("Controller Input")]
        public string horizontalInput = "Horizontal";
        public string verticallInput = "Vertical";
        public KeyCode jumpInput = KeyCode.Space;
        public KeyCode strafeInput = KeyCode.Tab;
        public KeyCode sprintInput = KeyCode.LeftShift;

        [Header("Camera Input")]
        public string rotateCameraXInput = "Mouse X";
        public string rotateCameraYInput = "Mouse Y";

        [HideInInspector] public vThirdPersonController cc;
        [HideInInspector] public vThirdPersonCamera tpCamera;
        [HideInInspector] public Camera cameraMain;

        #endregion

        protected virtual void Start()
        {
            InitilizeController();
            InitializeTpCamera();
        }

        protected virtual void FixedUpdate()
        {
            cc.UpdateMotor();               // updates the ThirdPersonMotor methods
            cc.ControlLocomotionType();     // handle the controller locomotion type and movespeed
            cc.ControlRotationType();       // handle the controller rotation type
        }

        protected virtual void Update()
        {
            InputHandle();                  // update the input methods
            cc.UpdateAnimator();            // updates the Animator Parameters
        }

        public virtual void OnAnimatorMove()
        {
            cc.ControlAnimatorRootMotion(); // handle root motion animations 
        }

        #region Basic Locomotion Inputs

        protected virtual void InitilizeController()
        {
            cc = GetComponent<vThirdPersonController>();

            if (cc != null)
                cc.Init();
        }

        protected virtual void InitializeTpCamera()
        {
            if (tpCamera == null)
            {
                tpCamera = FindObjectOfType<vThirdPersonCamera>();
                if (tpCamera == null)
                    return;
                if (tpCamera)
                {
                    tpCamera.SetMainTarget(this.transform);
                    tpCamera.Init();
                }
            }
        }

        protected virtual void InputHandle()
        {
            MoveInput();
            CameraInput();
            SprintInput();
            StrafeInput();
            JumpInput();
        }


        public GameObject box;
        float zButton = 0 ; 
        public bool isBox;
        float X;
        float Y;

        public virtual void MoveInput()
        {
            if(isBox){
            bool forward = box.GetComponent<BoxManager>().rightButton;
            bool backward = box.GetComponent<BoxManager>().bottomButton;
            if(forward){
                zButton=1;
            }
            else if(backward){
                zButton=-1;
            }
            else{
                zButton=0;
            }
            cc.input.z = zButton;
            }
            else{
            cc.input.x = Input.GetAxis(horizontalInput);
            cc.input.z = Input.GetAxis(verticallInput);
            }
        }

        protected virtual void CameraInput()
        {
            if (!cameraMain)
            {
                if (!Camera.main) Debug.Log("Missing a Camera with the tag MainCamera, please add one.");
                else
                {
                    cameraMain = Camera.main;
                    cc.rotateTarget = cameraMain.transform;
                }
            }

            if (cameraMain)
            {
                cc.UpdateMoveDirection(cameraMain.transform);
            }

            if (tpCamera == null)
                return;
            if(isBox){
            float joyX = box.GetComponent<BoxManager>().joyX;
            float joyY = box.GetComponent<BoxManager>().joyY;
            
            X = joyX;
            Y = joyY;
            // if(Mathf.Abs(X) <0.6){
            //     X=0;
            // }
            // if(Mathf.Abs(Y) <0.6){
            //     Y=0;
            // }
            // Debug.Log(X);
            // Debug.Log(Y);
            }
            else{
            Y = Input.GetAxis(rotateCameraYInput);
            X = Input.GetAxis(rotateCameraXInput);
            }
            tpCamera.RotateCamera(X*2, Y*2);
        }

        protected virtual void StrafeInput()
        {
            if (Input.GetKeyDown(strafeInput))
                cc.Strafe();
        }

        protected virtual void SprintInput()
        {
            if (Input.GetKeyDown(sprintInput))
                cc.Sprint(true);
            else if (Input.GetKeyUp(sprintInput))
                cc.Sprint(false);
        }

        /// <summary>
        /// Conditions to trigger the Jump animation & behavior
        /// </summary>
        /// <returns></returns>
        protected virtual bool JumpConditions()
        {
            return cc.isGrounded && cc.GroundAngle() < cc.slopeLimit && !cc.isJumping && !cc.stopMove;
        }

        /// <summary>
        /// Input to trigger the Jump 
        /// </summary>
        protected virtual void JumpInput()
        {
            if(isBox){
                bool topButton = box.GetComponent<BoxManager>().topButton;
                if (topButton && JumpConditions()){
                cc.Jump();
            }
            }
            else{
                if (Input.GetKeyDown(jumpInput) && JumpConditions())
                {
                 cc.Jump();   
                }
            }
        }

        #endregion       
    }
}