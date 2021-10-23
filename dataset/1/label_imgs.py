import os
import cv2

class ManualImgLabeler:
    def __init__(self) -> None:
        self.img = None
        self.refpt = None
        self.name = None

    def __bool__(self):
        assert self.name != None
        if os.path.exists(f"../labels/{self.name}.txt"):
            return False
        return True

    def cutdown_name(self, path: str):
        name_ind = path.find("/")
        if name_ind != -1:
            return self.cutdown_name(path[name_ind+1:])
        png = path.find(".png")
        if png != -1:
            path = path[:png]
        return path
    
    def open_img(self, path):
        self.name = self.cutdown_name(path)
        img = cv2.imread(path)
        self.img = cv2.resize(img, (416,416))

    def display_img(self):
        cv2.namedWindow(self.name)
        cv2.setMouseCallback(self.name, self.click)
        self.refpt = None
        refpts = []
        while(True):
            img = self.img.copy()
            if self.refpt:
                if refpts:
                    for detection in refpts:
                        cv2.rectangle(img, tuple(detection[0]), tuple(detection[1]), (255, 0, 0), 1)
                cv2.rectangle(img, tuple(self.refpt[0]), tuple(self.refpt[1]), (0, 255, 0), 1)
            cv2.imshow(self.name, img)
            key = cv2.waitKey(0) & 0xFF
            if key == ord('q'):
                cv2.destroyAllWindows()
                return refpts
            elif key == ord('w'):
                self.refpt[0][1] -= 1
            elif key == ord('d'):
                self.refpt[0][0] += 1
            elif key == ord('s'):
                self.refpt[0][1] += 1
            elif key == ord('a'):
                self.refpt[0][0] -= 1
            elif key == ord('t'):
                self.refpt[1][1] -= 1
            elif key == ord('h'):
                self.refpt[1][0] += 1
            elif key == ord('g'):
                self.refpt[1][1] += 1
            elif key == ord('f'):
                self.refpt[1][0] -= 1
            elif key == ord('r'):
                refpts.append(tuple(self.refpt))
            elif key == ord('o'):
                cv2.destroyAllWindows()
                exit()
            elif key == ord('z'):
                refpts = []

    def click(self, event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            self.refpt = [[x, y]]

        if event == cv2.EVENT_LBUTTONUP:
            self.refpt.append([x, y])

    def write_to_file(self, refpts, n):
        assert len(refpts) == int(n)
        with open("../labels/" + self.name + ".txt", 'w') as file:
            file.writelines(self.name + 2*"\n")
            for refpt in refpts:
                file.writelines("Detection\n")
                file.writelines(f"top_left: {refpt[0]}\n")
                file.writelines(f"bottom_right: {refpt[1]}\n")
                file.writelines("\n")
                file.flush()

if __name__ == "__main__":
    labeler = ManualImgLabeler()

    len_imgs = len(os.listdir(r'.'))
    for filename in os.listdir(r'.'):
        len_txt = len(os.listdir(r'../labels'))
        if filename.endswith('.png'):
            labeler.open_img(filename)
            if (labeler):
                refpts = labeler.display_img()
                n = input(f"({len_txt}/{len_imgs}) How many detections in file {labeler.name}? ")
                if n == "":
                    n = 1
                labeler.write_to_file(refpts, n)
