import math
from time import sleep

import cv2
import mediapipe as mp
import pyautogui
from pynput.keyboard import Key, Controller

mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_hands = mp.solutions.hands


def euclideanDistance(landmark1, landmark2):
    return math.sqrt((landmark1.x - landmark2.x)**2 + (landmark1.y - landmark2.y)**2 + (landmark1.z - landmark2.z)**2)


def slope(landmark1, landmark2):
    if (landmark1.x - landmark2.x == 0):
        return math.inf
    return (landmark2.y - landmark1.y) / (landmark2.x - landmark1.x)

# For static images:
# IMAGE_FILES = ["assets/1.jpg"]
# with mp_hands.Hands(
#     static_image_mode=True,
#     max_num_hands=2,
#     min_detection_confidence=0.5) as hands:
#   for idx, file in enumerate(IMAGE_FILES):
#     # Read an image, flip it around y-axis for correct handedness output (see
#     # above).
#     image = cv2.flip(cv2.imread(file), 1)
#     # Convert the BGR image to RGB before processing.
#     results = hands.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

#     # Print handedness and draw hand landmarks on the image.
#     print('Handedness:', results.multi_handedness)
#     if not results.multi_hand_landmarks:
#       continue
#     image_height, image_width, _ = image.shape
#     annotated_image = image.copy()
#     for hand_landmarks in results.multi_hand_landmarks:
#       print('hand_landmarks:', hand_landmarks)
#       print(
#           f'Index finger tip coordinates: (',
#           f'{hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP].x * image_width}, '
#           f'{hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP].y * image_height})'
#       )
#       mp_drawing.draw_landmarks(
#           annotated_image,
#           hand_landmarks,
#           mp_hands.HAND_CONNECTIONS,
#           mp_drawing_styles.get_default_hand_landmarks_style(),
#           mp_drawing_styles.get_default_hand_connections_style())
#     print("distance: ", euclideanDistance(hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
#                                           hand_landmarks.landmark[mp_hands.HandLandmark.WRIST]))
#     cv2.imwrite(
#         '/tmp/annotated_image' + str(idx) + '.png', cv2.flip(annotated_image, 1))
#     # Draw hand world landmarks.
#     if not results.multi_hand_world_landmarks:
#       continue
#     for hand_world_landmarks in results.multi_hand_world_landmarks:
#       mp_drawing.plot_landmarks(
#         hand_world_landmarks, mp_hands.HAND_CONNECTIONS, azimuth=5)


frame = 0
initialX = 0
initalY = 0
spaceWasPressed = False
keyboard = Controller()

# For webcam input:
cap = cv2.VideoCapture(0)
with mp_hands.Hands(
        model_complexity=0,
        min_detection_confidence=0.5,
        min_tracking_confidence=0.5) as hands:
    while cap.isOpened():
        success, image = cap.read()
        if not success:
            print("Ignoring empty camera frame.")
            # If loading a video, use 'break' instead of 'continue'.
            continue

        # To improve performance, optionally mark the image as not writeable to
        # pass by reference.
        image.flags.writeable = False
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # print("Image shape:", image.shape)
        results = hands.process(image)

        # Draw the hand annotations on the image.
        image.flags.writeable = True
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        # if results.multi_hand_world_landmarks and (len(results.multi_hand_world_landmarks) == 2):
        #     # print("MULTI_HAND_WORLD_LANDMARKS: ", len(results.multi_hand_world_landmarks))
        #     # print("2 hands")
        #     # print(results.multi_hand_world_landmarks[0])
        #     print(type(results.multi_hand_world_landmarks))
        #     print(results.multi_hand_world_landmarks[0].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP].x,
        #           results.multi_hand_world_landmarks[1].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP].x)

        #     print("distance: ", euclideanDistance(results.multi_hand_world_landmarks[0].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
        #           results.multi_hand_world_landmarks[1].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]))

        if results.multi_hand_landmarks:
            # if len(results.multi_hand_landmarks) == 2:
            #     # print(results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP].x,
            #     #       results.multi_hand_landmarks[1].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP].x)
            #     # print(slope(results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
            #     #             results.multi_hand_landmarks[1].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]))
            #     s = slope(results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
            #                 results.multi_hand_landmarks[1].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP])
            #     if (s >= 0.1):
            #         pyautogui.press("left")
            #     elif (s <= -0.1):
            #         pyautogui.press("right")
            #     elif (-0.1 < s and s < 0.1):
            #         pyautogui.press("up")

            if (frame == 0):
                frame += 1
                initialX = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].x
                initialY = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].y
                print(f"initialX: {initialX}")
                print(f"initialY: {initialY}")
            dx = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].x - initialX
            dy = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].y - initialY
            leftDist = euclideanDistance(results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
                                         results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.THUMB_TIP])

            # print(f"dx: {dx}; dy: {dy}; leftDist: {leftDist}")

            # Fireball
            if (leftDist < 0.1):
                if (not spaceWasPressed):
                    print("Space")
                    spaceWasPressed = True
                    keyboard.press(Key.space)
                    # sleep(0.1)
                    keyboard.release(Key.space)
                    # pyautogui.press("space")
            else:
                spaceWasPressed = False

            val = 0.2
            # Controls
            if (dx > val):
                print("Left")
                keyboard.press(Key.left)
                keyboard.release(Key.left)
                # pyautogui.press("left")
            elif (dx < -val):
                print("Right")
                keyboard.press(Key.right)
                keyboard.release(Key.right)
                # pyautogui.press("right")

            if (dy > val):
                print("Down")
                keyboard.press(Key.down)
                keyboard.release(Key.down)
                # pyautogui.press("down")
            elif (dy < -val):
                print("Up")
                keyboard.press(Key.up)
                keyboard.release(Key.up)
                # pyautogui.press("up")

            # if len(results.multi_hand_landmarks) == 2:
            #     if (frame == 0):
            #         frame += 1
            #         initialX = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].x
            #         initialY = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].y
            #         print(f"initialX: {initialX}")
            #         print(f"initialY: {initialY}")
            #     dx = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].x - initialX
            #     dy = results.multi_hand_landmarks[0].landmark[mp_hands.HandLandmark.MIDDLE_FINGER_MCP].y - initalY
            #     leftDist = euclideanDistance(results.multi_hand_landmarks[1].landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
            #                                  results.multi_hand_landmarks[1].landmark[mp_hands.HandLandmark.THUMB_TIP])

            #     print(f"dx: {dx}; dy: {dy}; leftDist: {leftDist}")

            #     # Fireball
            #     # if (leftDist < 0.3):
            #     #     pyautogui.press("space")

            #     val = 0.05
            #     keyboard = Controller()

            #     # Controls
            #     if (dx > val):
            #         keyboard.press(Key.right)
            #         keyboard.release(Key.right)
            #         # pyautogui.press("right")
            #     elif (dx < val):
            #         keyboard.press(Key.left)
            #         keyboard.release(Key.left)
            #         # pyautogui.press("left")

            #     if (dy > val):
            #         keyboard.press(Key.up)
            #         keyboard.release(Key.up)
            #         # pyautogui.press("up")
            #     elif (dy < val):
            #         keyboard.press(Key.down)
            #         keyboard.release(Key.down)
            #         # pyautogui.press("down")

            # print(len(results.multi_hand_landmarks))
            # for hand_landmarks in results.multi_hand_landmarks:
            #     # print("distance: ", euclideanDistance(hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP],
            #     #                                   hand_landmarks.landmark[mp_hands.HandLandmark.WRIST]))
            #     mp_drawing.draw_landmarks(
            #         image,
            #         hand_landmarks,
            #         mp_hands.HAND_CONNECTIONS,
            #         mp_drawing_styles.get_default_hand_landmarks_style(),
            #         mp_drawing_styles.get_default_hand_connections_style())
        # Flip the image horizontally for a selfie-view display.
        # cv2.imshow('MediaPipe Hands', cv2.flip(image, 1))
        if cv2.waitKey(5) & 0xFF == 27:
            break
cap.release()
