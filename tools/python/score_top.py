import os

class ScoreTop:
    def __init__(self, map_file):
        self.map_file = map_file
    
    def display_top_files(self, scoreFiles, showTopFiles, exclude_lib=False):        
        # Build list of files with their TODO and DONE sizes
        files_data = []
        total_todo_size = 0
        total_done_size = 0
        
        for scoreFile in scoreFiles:
            # Skip libultra files if exclude_lib is True
            if exclude_lib and '/libultra/' in scoreFile.path:
                continue
            
            # Skip non-C files or files without path
            if not scoreFile.path.endswith('.c'):
                continue
            
            todo_size = scoreFile.unfinishedSize  # GLOBAL_ASM functions still need work
            done_size = scoreFile.get_size_of_functions()  # Decompiled functions
            
            # Only include files that have some work (TODO or DONE)
            if todo_size > 0 or done_size > 0:
                total_file_size = todo_size + done_size
                
                if total_file_size > 0:
                    todo_percentage = (todo_size / total_file_size) * 100
                    done_percentage = (done_size / total_file_size) * 100
                else:
                    todo_percentage = 0
                    done_percentage = 100
                
                # Skip files that are 100% complete (no TODO remaining)
                if todo_size == 0:
                    continue
                
                files_data.append({
                    'name': os.path.basename(scoreFile.path),
                    'path': scoreFile.path,
                    'todo_size': todo_size,
                    'done_size': done_size,
                    'total_size': total_file_size,
                    'todo_percentage': todo_percentage,
                    'done_percentage': done_percentage
                })
                
                total_todo_size += todo_size
                total_done_size += done_size
        
        if not files_data:
            print("\n✓ No C files with remaining GLOBAL_ASM found!")
            return
        
        # Sort by TODO size (largest first) - files that need most work
        files_data.sort(key=lambda x: x['todo_size'], reverse=True)
        
        # Limit to top N
        top_files = files_data[:showTopFiles]
        
        # Calculate totals
        total_all = total_todo_size + total_done_size
        
        # Print header
        print('=' * 95)
        print(f"{'File':<40} {'TODO':>10} {'DONE':>10} {'Remaining%':>12} {'Complete%':>12}")
        print('-' * 95)
        
        # Print each file
        for file_data in top_files:
            # Truncate name if too long
            name = file_data['name']
            if len(name) > 40:
                name = name[:37] + '...'
                
            print(f"{name:<40} "
                  f"{file_data['todo_size']:>10} "
                  f"{file_data['done_size']:>10} "
                  f"{file_data['todo_percentage']:>11.2f}% "
                  f"{file_data['done_percentage']:>11.2f}%")
        
        # Show if there are more files
        if len(files_data) > showTopFiles:
            remaining_count = len(files_data) - showTopFiles
            print('-' * 95)
            print(f"  ... and {remaining_count} more file(s) with remaining GLOBAL_ASM")
        
        # Show summary for all files
        if total_all > 0:
            print('-' * 95)
            print(f"{'Total':<40} "
                  f"{total_todo_size:>10} "
                  f"{total_done_size:>10} "
                  f"{((total_todo_size / total_all) * 100):>11.2f}% "
                  f"{((total_done_size / total_all) * 100):>11.2f}%")
        
        print('=' * 95)
