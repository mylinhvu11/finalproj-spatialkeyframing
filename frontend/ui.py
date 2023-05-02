import streamlit as st
import cv2
import mediapipe as mp
from mediapipe.framework.formats import landmark_pb2
import numpy as np

mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose
pose = mp_pose.Pose(static_image_mode=False, model_complexity=1, min_detection_confidence=0.5, min_tracking_confidence=0.5)

def process_frame(img):
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    result = pose.process(img_rgb)

    if result.pose_landmarks:
        mp_drawing.draw_landmarks(img, result.pose_landmarks, mp_pose.POSE_CONNECTIONS)

    return img, result

st.title("Real-time Pose Estimation")

if "capture_button_clicked" not in st.session_state:
    st.session_state.capture_button_clicked = False

if st.button("Capture"):
    st.session_state.capture_button_clicked = not st.session_state.capture_button_clicked

if "captured_images" not in st.session_state:
    st.session_state.captured_images = []

if "captured_poses" not in st.session_state:
    st.session_state.captured_poses = []

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

# Create columns for webcam view and image previews
webcam_col, previews_col = st.columns(2)
video_stream_placeholder = webcam_col.empty()
previews_placeholder = previews_col.empty()
alert = st.empty()

while True:
    ret, frame = cap.read()
    if not ret:
        st.warning("Error accessing the camera.")
        break

    frame = cv2.flip(frame, 1)
    processed_frame, pose_data = process_frame(frame)
    processed_frame_rgb = cv2.cvtColor(processed_frame, cv2.COLOR_BGR2RGB)

    video_stream_placeholder.image(processed_frame_rgb, channels="RGB", output_format="JPEG")

    if st.session_state.capture_button_clicked:
        if pose_data.pose_landmarks is not None:
            st.session_state.captured_images.append(processed_frame_rgb.copy())
            st.session_state.captured_poses.append(pose_data)
            st.session_state.capture_button_clicked = False
            alert.empty()
        else:
            alert.error('This is an error', icon="🚨")

    # Display image previews
    previews_container = previews_placeholder.container()
    for i, img in enumerate(st.session_state.captured_images):
        img_copy = img.copy()
        if st.session_state.captured_poses[i].pose_landmarks:
            mp_drawing.draw_landmarks(img_copy, st.session_state.captured_poses[i].pose_landmarks, mp_pose.POSE_CONNECTIONS)
        previews_container.image(img_copy, channels="RGB", output_format="JPEG")


cap.release()
