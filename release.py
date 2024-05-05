import os
import shutil
from sys import argv

name = argv[1]


release_folder = f"Release{name}"
exe_source = f"out/{name}.exe"
dll_source_folder = "dlls/"
resource_folder = "res/"

print("-- Создание папки релиза")
if not os.path.exists(release_folder):
    os.makedirs(release_folder)

print("-- Копирование exe файла")
shutil.copy(exe_source, release_folder)

print("-- Копирование всех DLL файлов")
for file in os.listdir(dll_source_folder):
    full_file_name = os.path.join(dll_source_folder, file)
    if os.path.isfile(full_file_name):
        shutil.copy(full_file_name, release_folder)

print("-- Копирование папки ресурсов")
shutil.copytree(resource_folder, os.path.join(release_folder, "res"))

print("-- Упаковка папки релиза в tar.gz")
shutil.make_archive(release_folder, 'gztar', release_folder)

print("-- Удаление исходной папки релиза")
shutil.rmtree(release_folder)

print("-- Готово --")