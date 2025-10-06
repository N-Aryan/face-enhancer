# Face Enhancer (C++ & OpenCV)

A computer vision project that enhances **blurred face images** using classic image processing techniques in C++.  
It applies **sharpening**, **contrast enhancement (CLAHE)**, and **color denoising**, followed by an **automatic sharpness evaluation** to measure improvement.  
The project was written entirely from scratch for an internship assignment.

---

## 🧠 Features
- 3×3 sharpening kernel to restore edge clarity.  
- CLAHE (Contrast Limited Adaptive Histogram Equalization) for balanced lighting and vivid details.  
- `fastNlMeansDenoisingColored()` to remove color noise.  
- Automatic **sharpness measurement** before and after enhancement using Laplacian variance.  
- Auto-generated **side-by-side comparison images** for demo and analysis.  

---

## 🗂 Folder Structure
```
face-enhancer/
├─ images/        # Input blurred face images
├─ output/        # Enhanced and comparison outputs
└─ main.cpp       # Main program
```

---

## ⚙️ How to Build & Run

### 🧩 Linux / macOS
```bash
g++ main.cpp -o face_enhancer `pkg-config --cflags --libs opencv4`
./face_enhancer
```
🧩 Windows (MinGW)
```
g++ main.cpp -o face_enhancer -IC:\opencv\build\include ^
-LC:\opencv\build\x64\mingw\lib ^
-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_photo
face_enhancer.exe
```
