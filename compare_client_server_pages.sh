scp ssaqib@128.105.145.95:/filecachemonitor/server_cached_pages.txt .
scp ssaqib@128.105.144.226:/filecachemonitor/client_cached_pages.txt .

python compare_caches.py
